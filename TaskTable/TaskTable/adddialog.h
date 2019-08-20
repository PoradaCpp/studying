#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QDateTimeEdit>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = nullptr);

    QString name() const;
    uint32_t priority() const;
    QDateTime deadTime() const;
    void editPriority(const QString &name, uint32_t priority);
    void editDeadTime(const QString &name, QDateTime deadTime);

private:
    QLineEdit *m_pNameText;
    QSpinBox *m_pPriority;
    QDateTimeEdit *m_pDeadTimeEdit;
};

#endif // ADDDIALOG_H

