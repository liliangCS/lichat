#ifndef EMOJIBTN_H
#define EMOJIBTN_H

#include <QObject>
#include <QPushButton>

class EmojiBtn : public QPushButton
{
    Q_OBJECT
public:
    EmojiBtn(QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *event);
};

#endif // EMOJIBTN_H
