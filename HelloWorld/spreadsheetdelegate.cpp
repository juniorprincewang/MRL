#include "spreadsheetdelegate.h"

#include <QtWidgets>

SpreadSheetDelegate::SpreadSheetDelegate(QObject *parent)
        : QItemDelegate(parent) {}

QWidget *SpreadSheetDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &index) const
{
    if (index.column() == 1) {
        QDateTimeEdit *editor = new QDateTimeEdit(parent);
        editor->setDisplayFormat("dd/M/yyyy");
        editor->setCalendarPopup(true);
        return editor;
    }
    else if(index.column() == 3)
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItem(QString("1"));
        editor->addItem(QString("2"));
        editor->addItem(QString("3"));
//        editor->installEventFilter(const_cast<SpreadSheetDelegate*>(this));
        return editor;
    }
    QLineEdit *editor = new QLineEdit(parent);

    // create a completer with the strings in the column as model
    QStringList allStrings;
    for (int i = 1; i<index.model()->rowCount(); i++) {
        QString strItem(index.model()->data(index.sibling(i, index.column()),
            Qt::EditRole).toString());

        if (!allStrings.contains(strItem))
            allStrings.append(strItem);
    }

    QCompleter *autoComplete = new QCompleter(allStrings);
    editor->setCompleter(autoComplete);
    connect(editor, &QLineEdit::editingFinished, this, &SpreadSheetDelegate::commitAndCloseEditor);
    return editor;
}

void SpreadSheetDelegate::commitAndCloseEditor()
{
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void SpreadSheetDelegate::setEditorData(QWidget *editor,
    const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(editor);
    if (edit) {
        edit->setText(index.model()->data(index, Qt::EditRole).toString());
        return;
    }

    QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
    if (dateEditor) {
        dateEditor->setDate(QDate::fromString(
                                index.model()->data(index, Qt::EditRole).toString(),
                                "d/M/yyyy"));
        return;
    }
    QComboBox *comboEditor = qobject_cast<QComboBox *>(editor);
    if(comboEditor)
    {
        comboEditor->setCurrentText(index.model()->data(index, Qt::EditRole).toString());
        return;
    }

}

void SpreadSheetDelegate::setModelData(QWidget *editor,
    QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
    if (edit) {
        model->setData(index, edit->text());
        return;
    }

    QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
    if (dateEditor)
    {
        model->setData(index, dateEditor->date().toString("dd/M/yyyy"));
        return;
    }
    QComboBox *comboEditor = qobject_cast<QComboBox *>(editor);
    if(comboEditor)
    {
        model->setData(index, comboEditor->currentText());
        return;
    }
}
