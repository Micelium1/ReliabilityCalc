#ifndef SOLVER45_H
#define SOLVER45_H

#include <QDialog>

namespace Ui {
class Solver45;
}

class Solver45 : public QDialog
{
    Q_OBJECT

public:
    explicit Solver45(QWidget *parent = nullptr);
    ~Solver45();

private:
    Ui::Solver45 *ui;
};

#endif // SOLVER45_H
