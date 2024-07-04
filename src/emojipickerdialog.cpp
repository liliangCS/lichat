#include <QGridLayout>
#include <QDebug>
#include <qpushbutton.h>
#include <QMessageBox>
#include "ui_emojipickerdialog.h"
#include "include/emojipickerdialog.h"
#include "include/helper.h"


EmojiPickerDialog* EmojiPickerDialog::instance = nullptr;

EmojiPickerDialog::EmojiPickerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmojiPickerDialog), m_emojiPaths(new QStringList())
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(300, 150);
    Helper::loadStyleSheet(this, ":/qss/emojiPickerDialog.qss");
    initEmojiPaths();
    initEmojiGrid();
}

EmojiPickerDialog::~EmojiPickerDialog()
{
    delete ui;
}

void EmojiPickerDialog::leaveEvent(QEvent *event)
{
    if (this->isVisible())
    {
        this->close();
    }
    QDialog::leaveEvent(event);
}

EmojiPickerDialog *EmojiPickerDialog::getInstance()
{
    if (instance == nullptr)
    {
        instance = new EmojiPickerDialog();
    }
    return instance;
}

void EmojiPickerDialog::initEmojiPaths()
{
    for (int i = 0; i < 50; i++) {
        QString emojiPath = QString(":/emoji/%1.gif").arg(i);
        m_emojiPaths->append(emojiPath);
    }
}

void EmojiPickerDialog::initEmojiGrid()
{
    QGridLayout *layout = new QGridLayout(this);
    int row = 0;
    int col = 0;
    for (int i = 0; i < m_emojiPaths->size(); i++)
    {
        addEmojiButton(layout, row, col, m_emojiPaths->at(i), i);
        col++;
        if (col >= 10) {
            col = 0;
            row++;
        }
    }
}

void EmojiPickerDialog::addEmojiButton(QGridLayout *layout, int row, int col, const QString &iconPath, int index)
{
    QPushButton *button = new QPushButton(this);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(20, 20)); //设置表情图标大小
    connect(button, &QPushButton::clicked, this, [this, index](){
        emit emojiClicked(index);
    });
    layout->addWidget(button, row, col);
}
