#include "commanddialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QStandardPaths>

CommandDialog::CommandDialog(QWidget *parent)
    : QDialog(parent){
    setWindowTitle("指令列表管理");
    resize(500, 400);

    auto *mainLayout = new QVBoxLayout(this);

    m_list = new QListWidget;
    mainLayout->addWidget(m_list);

    auto *formLayout = new QFormLayout;
    m_nameEdit = new QLineEdit;
    m_contentEdit = new QLineEdit;
    m_hexCheck = new QCheckBox("HEX 模式");
    m_autoReplyPatternEdit = new QLineEdit;
    m_autoReplyPatternEdit->setPlaceholderText("自动回复匹配模式（留空=普通指令）");
    formLayout->addRow("名称:", m_nameEdit);
    formLayout->addRow("内容:", m_contentEdit);
    formLayout->addRow(m_hexCheck);
    formLayout->addRow("匹配:", m_autoReplyPatternEdit);
    mainLayout->addLayout(formLayout);

    auto *btnRow = new QHBoxLayout;
    m_addBtn = new QPushButton("添加");
    m_deleteBtn = new QPushButton("删除");
    btnRow->addWidget(m_addBtn);
    btnRow->addWidget(m_deleteBtn);
    btnRow->addStretch();
    mainLayout->addLayout(btnRow);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);

    connect(m_addBtn, &QPushButton::clicked, this, &CommandDialog::onAdd);
    connect(m_deleteBtn, &QPushButton::clicked, this, &CommandDialog::onDelete);
    connect(m_list, &QListWidget::currentRowChanged, this, [this](int row) {
        m_currentIndex = row;
        if (row >= 0 && row < m_commands.size()) {
            const auto &cmd = m_commands.at(row);
            m_nameEdit->setText(cmd.name);
            m_contentEdit->setText(cmd.content);
            m_hexCheck->setChecked(cmd.isHex);
            m_autoReplyPatternEdit->setText(cmd.autoReplyPattern);
        }
    });
    connect(m_nameEdit, &QLineEdit::editingFinished, this, &CommandDialog::onSaveField);
    connect(m_contentEdit, &QLineEdit::editingFinished, this, &CommandDialog::onSaveField);
    connect(m_hexCheck, &QCheckBox::toggled, this, [this]() { onSaveField(); });
    connect(m_autoReplyPatternEdit, &QLineEdit::editingFinished, this, &CommandDialog::onSaveField);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QList<CommandItem> CommandDialog::commands() const{
    return m_commands;
}

void CommandDialog::setCommands(const QList<CommandItem> &cmds){
    m_commands = cmds;
    m_list->clear();
    for (const auto &cmd : m_commands){
        m_list->addItem(cmd.name);
    }
}

void CommandDialog::onAdd(){
    CommandItem cmd;
    cmd.name = QString("指令 %1").arg(m_commands.size() + 1);
    cmd.content.clear();
    m_commands.append(cmd);
    m_list->addItem(cmd.name);
    m_list->setCurrentRow(m_commands.size() - 1);
    m_nameEdit->setFocus();
    m_nameEdit->selectAll();
}

void CommandDialog::onDelete(){
    int row = m_list->currentRow();
    if (row < 0 || row >= m_commands.size())
        return;
    m_commands.removeAt(row);
    delete m_list->takeItem(row);
    m_nameEdit->clear();
    m_contentEdit->clear();
    m_currentIndex = -1;
}

void CommandDialog::onSaveField(){
    int row = m_list->currentRow();
    if (row < 0 || row >= m_commands.size())
        return;
    m_commands[row].name = m_nameEdit->text();
    m_commands[row].content = m_contentEdit->text();
    m_commands[row].isHex = m_hexCheck->isChecked();
    m_commands[row].autoReplyPattern = m_autoReplyPatternEdit->text();
    m_list->item(row)->setText(m_commands[row].name);
}

QString CommandDialog::jsonFilePath(){
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+ "/commands.json";
}

QList<CommandItem> CommandDialog::loadFromFile(){
    QList<CommandItem> result;
    QFile file(jsonFilePath());
    if (!file.open(QIODevice::ReadOnly)){
        return result;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isArray()){
        return result;
    }

    for (const auto &val : doc.array()) {
        QJsonObject obj = val.toObject();
        CommandItem cmd;
        cmd.name = obj["name"].toString();
        cmd.content = obj["content"].toString();
        cmd.isHex = obj["isHex"].toBool();
        cmd.autoReplyPattern = obj["autoReplyPattern"].toString();
        result.append(cmd);
    }
    return result;
}

void CommandDialog::saveToFile(const QList<CommandItem> &cmds){
    QJsonArray arr;
    for (const auto &cmd : cmds) {
        QJsonObject obj;
        obj["name"] = cmd.name;
        obj["content"] = cmd.content;
        obj["isHex"] = cmd.isHex;
        obj["autoReplyPattern"] = cmd.autoReplyPattern;
        arr.append(obj);
    }
    QFile file(jsonFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(arr).toJson());
        file.close();
    }
}
