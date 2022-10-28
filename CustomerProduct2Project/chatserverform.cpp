#include "chatserverform.h"
#include "qtreewidget.h"
#include "ui_chatserverform.h"
#include "logthread.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>
#include <QMenu>
#include <QFile>
#include <QFileInfo>
#include <QProgressDialog>
#include <QDir>
#include <QCoreApplication>

ChatServerForm::ChatServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatServerForm), totalSize(0), byteReceived(0)
{
    ui->setupUi(this);
    QList<int> sizes;
    sizes << 120 << 500;
    ui->splitter->setSizes(sizes);

    chatServer = new QTcpServer(this); // 채팅용 소켓
    connect(chatServer, SIGNAL(newConnection( )), SLOT(clientConnect( )));
    if (!chatServer->listen(QHostAddress::Any, PORT_NUMBER)) { // 포트 연결 시도 네트워크 수신 대기 실패시 false 반환
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(chatServer->errorString( )));
        close( );
        return;
    }

    fileServer = new QTcpServer(this); // 파일 전송용 소켓
    connect(fileServer, SIGNAL(newConnection()), SLOT(acceptConnection()));
    if (!fileServer->listen(QHostAddress::Any, PORT_NUMBER+1)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(fileServer->errorString( )));
        close( );
        return;
    }

    qDebug("Start listening ...");

    QAction* inviteAction = new QAction(tr("&Invite"));
    inviteAction->setObjectName("Invite");
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));

    QAction* removeAction = new QAction(tr("&Kick out"));
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));

    menu = new QMenu;
    menu->addAction(inviteAction);
    menu->addAction(removeAction);
    ui->chatClientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    progressDialog = new QProgressDialog(0);
    progressDialog->setAutoClose(true);
    progressDialog->reset();

    logThread = new LogThread(this);
    logThread->start();

    connect(ui->savePushButton, SIGNAL(clicked()), logThread, SLOT(saveData()));

    qDebug() << tr("The server is running on port %1.").arg(chatServer->serverPort( ));
}

ChatServerForm::~ChatServerForm()
{
    delete ui;

    logThread->terminate();
    chatServer->close( );
    fileServer->close( );
}

void ChatServerForm::clientConnect( )
{
    QTcpSocket *clientConnection = chatServer->nextPendingConnection( ); // 대기중인 다음 연결을 반환해줌
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient()));
    qDebug("new connection is established...");
}

void ChatServerForm::receiveData( )
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( )); // 샌더는 readyRead 시그널을 보낸 소켓
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE); // 몇바이트 읽었나 확인하고 배열생성

    Chat_Status type;       // 채팅의 목적
    char data[1020];        // 전송되는 메시지/데이터
    memset(data, 0, 1020);

    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in.device()->seek(0);
    in >> type;
    in.readRawData(data, 1020);

    QString ip = clientConnection->peerAddress().toString(); // 연결상태면 피어 주소 반환 아닐시 NULL
    quint16 port = clientConnection->peerPort();
    QString name = QString::fromStdString(data);

    qDebug() << ip << " : " << type;

    switch(type) {
    case Chat_Login:
        foreach(auto item, ui->chatClientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "-") {
                item->setText(0, "-");
            }
            clientSocketHash[name] = clientConnection;
        }
        break;
    case Chat_In:
        foreach(auto item, ui->chatClientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "O") {
                item->setText(0, "O");
            }
            clientNameHash[port] = name;
            if(clientSocketHash.contains(name))
                clientSocketHash[name] = clientConnection;
        }
        break;
    case Chat_Talk: {
        foreach(QTcpSocket *sock, clientSocketHash.values()) {
            qDebug() << sock->peerPort();
             // 발신자 본인을 빼기 위해 넣은 조건문
            if(clientNameHash.contains(sock->peerPort()) && port != sock->peerPort()) {
                QByteArray sendArray;
                sendArray.clear();
                QDataStream out(&sendArray, QIODevice::WriteOnly);
                out << Chat_Talk;
                sendArray.append("<font color=lightsteelblue>");
                sendArray.append(clientNameHash[port].toStdString().data());
                sendArray.append("</font> : ");
                sendArray.append(name.toStdString().data());
                sock->write(sendArray);
                qDebug() << sock->peerPort();
            }
        }

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[clientNameHash[port]]));
        item->setText(3, clientNameHash[port]);
        item->setText(4, QString(data));
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, QString(data));
        ui->messageTreeWidget->addTopLevelItem(item);

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        logThread->appendData(item);
    }
        break;
    case Chat_Out:
        foreach(auto item, ui->chatClientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "-") {
                item->setText(0, "-");
            }
            clientNameHash.remove(port);
        }
        break;
    case Chat_LogOut:
        foreach(auto item, ui->chatClientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "X") {
                item->setText(0, "X");
            }
            clientSocketHash.remove(name);
        }
        break;
    }
}
//연결 해제
void ChatServerForm::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    if(clientConnection != nullptr) {
        QString name = clientNameHash[clientConnection->peerPort()];
        foreach(auto item, ui->chatClientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            item->setText(0, "X"); // 상태 변경
        }
        clientSocketHash.remove(name);
        clientConnection->deleteLater();
    }
}

void ChatServerForm::addClient(int id, QString name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->chatClientTreeWidget);
    item->setText(0, "X");
    item->setText(1, name);
    ui->chatClientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;
    ui->chatClientTreeWidget->resizeColumnToContents(0);
}

void ChatServerForm::on_chatClientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->chatClientTreeWidget->currentItem() == nullptr) // 등록된 유저가 없을 경우 우클릭 방지
        return;
    foreach(QAction *action, menu->actions()) {
        if(action->objectName() == "Invite")        // 초대
            action->setEnabled(ui->chatClientTreeWidget->currentItem()->text(0) != "O");
        else                                        // 강퇴
            action->setEnabled(ui->chatClientTreeWidget->currentItem()->text(0) == "O");
    }
    QPoint globalPos = ui->chatClientTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

/* 클라이언트 강퇴하기 */
void ChatServerForm::kickOut()
{
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_KickOut;
    out.writeRawData("", 1020);
     // currentItem이 NULLptr 일 경우 문제 발생
    QString name = ui->chatClientTreeWidget->currentItem()->text(1);
    QTcpSocket* sock = clientSocketHash[name];
    sock->write(sendArray);

    ui->chatClientTreeWidget->currentItem()->setText(0, "-");
}

/* 클라이언트 초대하기 */
void ChatServerForm::inviteClient()
{
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_Invite;
    out.writeRawData("", 1020);

    /* 소켓은 현재 선택된 아이템에 표시된 이름과 해쉬로 부터 가져온다. */
    QString name = ui->chatClientTreeWidget->currentItem()->text(1);
    QTcpSocket* sock = clientSocketHash[name];
    sock->write(sendArray);

    ui->chatClientTreeWidget->currentItem()->setText(0, "O");
}

/* 파일 전송을 위한 소켓 생성  확인*/
void ChatServerForm::acceptConnection()
{
    qDebug("연결 완료, 파일 전송 준비단계");

    QTcpSocket* receivedSocket = fileServer->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

/* 파일 전송 */
void ChatServerForm::readClient()
{
    qDebug("파일 다운로드 중...");
    QTcpSocket* receivedSocket = dynamic_cast<QTcpSocket *>(sender( ));
    QString filename, name;

    if (byteReceived == 0) {        // 파일 전송 시작 : 파일에 대한 정보를 이용해서 QFile 객체 생성
        progressDialog->reset();
        progressDialog->show();

        QString ip = receivedSocket->peerAddress().toString();
        quint16 port = receivedSocket->peerPort();
        qDebug() << ip << " : " << port;

        QDataStream in(receivedSocket);
        //totalSize, byteReceived, filename, name 을 읽어옴
        in >> totalSize >> byteReceived >> filename >> name;
        progressDialog->setMaximum(totalSize);

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[name]));
        item->setText(3, name);
        item->setText(4, filename);
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, filename);

        /* 컨텐츠의 길이로 QTreeWidget의 헤더의 크기를 고정 */
        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(item);
        logThread->appendData(item);

        QFileInfo info(filename);
        QString currentFileName = info.fileName();
        //qDebug() << currentFileName;
        // 프로젝트 파일의 워킹 디렉토리 경로확인
        QString projectPath = QCoreApplication::applicationDirPath();
        qDebug() << projectPath;
        QDir Dir(projectPath + "/../downlods");
        //다운로드 폴더 생성
        if(!Dir.exists())
        {
            Dir.mkdir(projectPath + "/../downlods");
        }
        file = new QFile(projectPath + "/../downlods/" + currentFileName);
        file->open(QFile::WriteOnly);
    } else {                    // 파일 데이터를 읽어서 저장
        inBlock = receivedSocket->readAll();
        byteReceived += inBlock.size();
        file->write(inBlock);
        file->flush();
    }

    progressDialog->setValue(byteReceived);

    if (byteReceived == totalSize) {        /* 파일의 다 읽으면 QFile 객체를 닫고 삭제 */
        qDebug() << QString("%1 수신 중....").arg(filename);

        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;
        progressDialog->reset();
        progressDialog->hide();

        file->close();
        delete file;
    }
}
