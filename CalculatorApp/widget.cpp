#include "widget.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_isFirst(true) {

    m_label = new QLabel("0", this);			// 레이블 객체의 생성
    m_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	// 계산기는 오른쪽 정렬
    m_label->setGeometry(10, 5, 230, 40);		// 위치와 크기 설정

    // 버튼에 표시될 문자열
    const char ButtonChar[16][2] = {
        "7", "8", "9", "/",	            // QPushButton 생성자의 첫번째 인자로 문자열만 사용 가능
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    // 슬롯들을 위한 배열
    const char *methods[16] = {
        SLOT(numButton( )), SLOT(numButton( )), SLOT(numButton( )), SLOT(opButton( )),
        SLOT(numButton( )), SLOT(numButton( )), SLOT(numButton( )), SLOT(opButton( )),
        SLOT(numButton( )), SLOT(numButton( )), SLOT(numButton( )), SLOT(opButton( )),
        SLOT(numButton( )), SLOT( ), SLOT( ), SLOT(opButton( ))
    };

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout-> setHorizontalSpacing(5);
    gridLayout-> setVerticalSpacing(5);

    for(int y = 0; y < WITDH; ++y) {		// 4 x 4의 2차원으로 배치
        for(int x = 0; x < WITDH; ++x) {
            int n = x+y*WITDH;		 	// 2차원 공간을 1차원으로 변환
            m_buttons.append(new QPushButton(ButtonChar[n], this));
            m_buttons.at(n)->resize(60, 60);
            if(n != 13 && n != 14)
                connect(m_buttons.at(n), SIGNAL(clicked( )), methods[n]);
            gridLayout -> addWidget(m_buttons.at(n),y,x);
        }
    }
#if 0
    // 숫자를 위한 버튼들의 시그널/슬롯 연결
    connect(m_buttons.at(0), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(1), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(2), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(4), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(5), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(6), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(8), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(9), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(10), SIGNAL(clicked( )), SLOT(numButton( )));
    connect(m_buttons.at(12), SIGNAL(clicked( )), SLOT(numButton( )));
#endif
    // Clear 버튼을 위한 시그널/슬롯 연결 : 람다 함수
    connect(m_buttons.at(13), &QPushButton::clicked, this, [=]( ){ m_label->setText("0"); });
#if 0
    // 연산자를 위한 버튼들을 위한 시그널/슬롯 연결
    connect(m_buttons.at(3), SIGNAL(clicked( )), SLOT(opButton( )));
    connect(m_buttons.at(7), SIGNAL(clicked( )), SLOT(opButton( )));
    connect(m_buttons.at(11), SIGNAL(clicked( )), SLOT(opButton( )));
    connect(m_buttons.at(15), SIGNAL(clicked( )), SLOT(opButton( )));
#endif
    // 계산을 위한 코드 : 람다 함수
    connect(m_buttons.at(14), &QPushButton::clicked, this, [this]( ){
        qreal result = 0;
        if(m_op == "+")           // 덧셈
            result = m_num1.toDouble( ) + m_label->text( ).toDouble( ); // QString을 double로
        else if(m_op == "-")      // 뺄셈
            result = m_num1.toDouble( ) - m_label->text( ).toDouble( );
        else if(m_op == "x")      // 곱셈
            result = m_num1.toDouble( ) * m_label->text( ).toDouble( );
        else if(m_op == "/")      // 나눗셈 : 에러 처리 필요
            result = m_num1.toDouble( ) / m_label->text( ).toDouble( );
        m_label->setText(QString::number(result));	// 숫자를 QString으로 변경
        m_isFirst = true;               // 새로운 값으로 입력
    });

    setMinimumSize(250, 295);           // 윈도우의 최소 크기 설정
    setMaximumSize(250, 295);           // 윈도우의 최대 크기 설정
    setWindowTitle("Calculator");		// 윈도우의 타이틀바 설정
}

Widget::~Widget( ) {			// 생성자에서 할당한 객체들의 정리 작업
    delete m_label;
    m_buttons.clear( );			// QVector 클래스 안의 객체 삭제
    //Q_FOREACH(auto b, m_buttons) delete b; 	// 수행시 에러 발생
}

void Widget::numButton( ) {		// 숫자 버튼이 눌려졌을 때의 처리
    // 시그널을 호출한 객체는 QObject::sender( ) 메소드로 받아올 수 있다.
    QPushButton* button = dynamic_cast<QPushButton*>(sender( ));
    QString bStr;
    if(button != nullptr) bStr = button->text( );	// 버튼의 문자열
    if(m_label != nullptr) {
        QString lStr = m_label->text( );		// 레이블의 문자열
        // 레이블의 문자가 0이면 버튼의 문자를 레이블에 그대로 설정
        // 0이 아니면 레이블의 문자열 + 버튼의 문자열을 레이블에 설정
        m_label->setText((lStr =="0"|m_isFirst)?bStr:lStr+bStr);
        m_isFirst = false;          // 기존의 값 뒤에 연결해서 입력
    }
}

void Widget::opButton( )
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender( ));
    if(button != nullptr) m_op = button->text( );	// 버튼의 문자열이 연산자
    if(m_label != nullptr) {
        m_num1 = m_label->text( );	// 현재 레이블의 문자열을 멤버 변수로 설정
        m_isFirst = true;           // m_label->setText("0");
    }
}
