#ifndef BANKDIALOG_H
#define BANKDIALOG_H

#include <QDialog>

class Company;

namespace Ui {
class BankDialog;
}

class BankDialog : public QDialog {
    Q_OBJECT

public:
    explicit BankDialog(QWidget *parent = nullptr);
    ~BankDialog();

    void updateDisplay();

	// Displays according to whether the client has lent money or not.
	void displayAccordingToClientStatus();

	inline void setClient(Company *client) { this->client_ = client; }

    static void setInterestRate(double interestRate) { interestRate_ = interestRate; }
    static const double interestRate() { return interestRate_; }

private slots:
	// Sets datas with the input.
    void on_pushButton_Accept_clicked();

private:
	// transforms double into QString
	static QString toString(double value);

    static double interestRate_;
    Company *client_;
    Ui::BankDialog *ui;
};

#endif // BANKDIALOG_H
