#include <QMessageBox>
#include <QRegularExpression>
#include "ui_homerightwidget.h"
#include "include/helper.h"
#include "include/chatroom.h"
#include "include/homerightwidget.h"
#include "include/emojipickerdialog.h"

HomeRightWidget::HomeRightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeRightWidget), m_contentStr(QString())
{
    ui->setupUi(this);
    Helper::loadStyleSheet(this, ":/qss/homeRightWidget.qss");

    //sendBtn
    connect(ui->sendBtn, &QPushButton::clicked, [this](){
        if (m_contentStr.trimmed() == "") {
            QMessageBox::information(this, "提示", "不允许输入空白字符");
            return;
        }

        if (m_emojiStr.isEmpty())
        {
            ChatRoom::getInstance()->sendPlainTextMsg(m_contentStr);
        }
        else
        {
            ChatRoom::getInstance()->sendRichTextMsg(m_contentStr, m_emojiStr);
        }
        clearInputChatMsg();
    });

    //emojiBtn
    connect(EmojiPickerDialog::getInstance(), &EmojiPickerDialog::emojiClicked, [this](int index){
        qDebug() << index;
        insertEmoji(ui->inputTextEdit, index);
    });

    //inputTextEdit
    connect(ui->inputTextEdit, &QTextEdit::textChanged, [this](){
        updateContentStr(ui->inputTextEdit->document()->toRawText());
    });
}

HomeRightWidget::~HomeRightWidget()
{
    delete ui;
}

void HomeRightWidget::updateUIChatMsg(QString &sender, QString &contentStr, QString &timeStr)
{
    QString chatMsgStr = QString(R"(
                        <p>
                            <span style="color: #888">%1&nbsp;</span>
                            <span style="color: red">%2</span>
                            <span style="color: green">说：</span>
                            <span style="color: blue">%3</span>
                        </p>
                        <br />
                      )").arg(timeStr).arg(sender).arg(contentStr);
    ui->chatTextEdit->insertHtml(chatMsgStr);
}

void HomeRightWidget::updateUIChatMsg2(QString &sender, QString &contentStr, QString &emojiStr, QString &timeStr)
{
    QStringList contentList = contentStr.split(QRegularExpression(""), Qt::KeepEmptyParts);

    contentList = contentList.mid(1, contentList.size() - 2);

    QStringList emojiList = emojiStr.mid(0, emojiStr.size()-1).split(";");


    for (QString &emojiPair : emojiList)
    {
        int cIndex = emojiPair.split(":").front().toInt();
        int eIndex = emojiPair.split(":").back().toInt();

        QString& contentItem = const_cast<QString&>(contentList.at(cIndex));
        contentItem = QString(R"(<img style="vertical-align: top" src=":/emoji/%1.gif" />)").arg(eIndex);
    }

    contentStr = contentList.join("");

    QString chatMsgStr = QString(R"(
                        <p>
                            <span style="color: #888">%1&nbsp;</span>
                            <span style="color: red">%2</span>
                            <span style="color: green">说：</span>
                            <span style="color: blue">%3</span>
                        </p>
                        <br />
                      )").arg(timeStr).arg(sender).arg(contentStr);

    ui->chatTextEdit->insertHtml(chatMsgStr);
}

void HomeRightWidget::clearRoomChatMsg()
{
    ui->chatTextEdit->clear();
}

void HomeRightWidget::insertEmoji(QTextEdit *textEdit, int emojiIndex)
{
    QString emojiStr = QString("<img src=':/emoji/%1.gif' style='vertical-align: top' />").arg(emojiIndex);
    updateEmojiStr(emojiIndex);
    textEdit->insertHtml(emojiStr);
}

void HomeRightWidget::updateContentStr(const QString &contentStr)
{
    m_contentStr = contentStr;
}


void HomeRightWidget::updateEmojiStr(int emojiIndex)
{
    //获取光标位置
    int cursorIndex = ui->inputTextEdit->textCursor().position();

    QString emoji = QString::number(cursorIndex) + ":" + QString::number(emojiIndex) + ";";
    m_emojiStr += emoji;
}

void HomeRightWidget::clearInputChatMsg()
{
    ui->inputTextEdit->clear();
    m_contentStr = "";
    m_emojiStr = "";
}
