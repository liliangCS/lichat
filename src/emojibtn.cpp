#include <QDebug>
#include "include/emojibtn.h"
#include "include/emojipickerdialog.h"

EmojiBtn::EmojiBtn(QWidget *parent): QPushButton(parent)
{

}

void EmojiBtn::enterEvent(QEvent *event)
{
    EmojiPickerDialog* emojiPickerDialog = EmojiPickerDialog::getInstance();
    if (!emojiPickerDialog->isVisible()) {
        int emojiPickerHight = emojiPickerDialog->size().height();
        QPoint pos = this->mapToGlobal(QPoint(0, 0));
        emojiPickerDialog->move(pos.x() - 10, pos.y() - emojiPickerHight - 10);
        emojiPickerDialog->show();
    }
    QPushButton::enterEvent(event);
}
