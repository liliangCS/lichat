#ifndef EMOJIPICKERDIALOG_H
#define EMOJIPICKERDIALOG_H

#include <QDialog>
#include <QGridLayout>

namespace Ui {
class EmojiPickerDialog;
}

class EmojiPickerDialog : public QDialog
{
    Q_OBJECT

public:
    EmojiPickerDialog(const EmojiPickerDialog&) = delete;
    EmojiPickerDialog& operator=(const EmojiPickerDialog&) = delete;

    static EmojiPickerDialog* getInstance();

    void initEmojiPaths();
    void initEmojiGrid();

    void addEmojiButton(QGridLayout *layout, int row, int col, const QString &iconPath, int index);

    ~EmojiPickerDialog();

protected:
    void leaveEvent(QEvent *event);

private:
    explicit EmojiPickerDialog(QWidget *parent = nullptr);
    static EmojiPickerDialog *instance;

    Ui::EmojiPickerDialog *ui;
    QStringList *m_emojiPaths;

signals:
    void emojiClicked(int index);
};

#endif // EMOJIPICKERDIALOG_H
