#ifndef INSTRUCTIONSDIALOG_HH
#define INSTRUCTIONSDIALOG_HH

#include <QDialog>

namespace Ui {
class InstructionsDialog;
}

class InstructionsDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief InstructionsDialog Construct an instruction dialog.
     * \param parent Parent window.
     */
    explicit InstructionsDialog(QWidget *parent = 0);
    ~InstructionsDialog();

private:
    Ui::InstructionsDialog *ui;
};

#endif // INSTRUCTIONSDIALOG_HH
