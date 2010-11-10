#ifndef IICM_GUI_H
#define IICM_GUI_H

#include <QDialog>

class iicm_gui : public QDialog
{
    Q_OBJECT

public:
    iicm_gui(QWidget *parent = 0);
    ~iicm_gui();

    float* prizes;
    int* stacks;
    int players;
    int* blinds;
};

#endif // IICM_GUI_H
