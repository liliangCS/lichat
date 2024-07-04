#ifndef HOMERIGHTWIDGET_H
#define HOMERIGHTWIDGET_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class HomeRightWidget;
}

class HomeRightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeRightWidget(QWidget *parent = nullptr);
    ~HomeRightWidget();

    void updateUIChatMsg(QString &sender, QString &contentStr, QString &timeStr);
    void updateUIChatMsg2(QString &sender, QString &contentStr, QString &emojiStr, QString &timeStr);

    void clearRoomChatMsg();

    void insertEmoji(QTextEdit *textEdit, int emojiIndex);
    void updateContentStr(const QString &contentStr);
    void updateEmojiStr(int emojiIndex);
    void clearInputChatMsg();

private:
    Ui::HomeRightWidget *ui;

    QString m_contentStr;
    QString m_emojiStr;
};

#endif // HOMERIGHTWIDGET_H
