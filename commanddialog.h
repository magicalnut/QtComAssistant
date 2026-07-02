#ifndef COMMANDDIALOG_H
#define COMMANDDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QJsonArray>

struct CommandItem {
    QString name;
    QString content;       // 发送内容（普通指令）或回复内容（自动回复规则）
    QString autoReplyPattern; // 自动回复的匹配模式（为空则非自动回复规则）
    bool isHex = false;
};

class CommandDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CommandDialog(QWidget *parent = nullptr);

    QList<CommandItem> commands() const;
    void setCommands(const QList<CommandItem> &cmds);

private slots:
    void onAdd();
    void onDelete();
    void onSaveField();

private:
    QListWidget *m_list = nullptr;
    QLineEdit *m_nameEdit = nullptr;
    QLineEdit *m_contentEdit = nullptr;
    QCheckBox *m_hexCheck = nullptr;
    QLineEdit *m_autoReplyPatternEdit = nullptr;
    QPushButton *m_addBtn = nullptr;
    QPushButton *m_deleteBtn = nullptr;

    QList<CommandItem> m_commands;
    int m_currentIndex = -1;
};

#endif // COMMANDDIALOG_H
