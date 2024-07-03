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
    explicit EmojiPickerDialog(QWidget *parent = nullptr);
    ~EmojiPickerDialog();

    void initEmojiPaths();
    void initEmojiGrid();

    void addEmojiButton(QGridLayout *layout, int row, int col, const QString &iconPath, int index);

private:
    Ui::EmojiPickerDialog *ui;

    QStringList *m_emojiPaths;


public slots:
    void onEmojiClicked(int index);
};

#endif // EMOJIPICKERDIALOG_H
