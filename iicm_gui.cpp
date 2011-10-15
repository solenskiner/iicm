#include "iicm_gui.hpp"
#include <string>
extern "C" {
  #include "calc_icm.h"
  #include <stdlib.h>
  #include "misc_helpers.h"
}
#include <QValidator>
#include <QVariant>

int line_edit::_n = 0;

iicm_gui::iicm_gui() {
  layout = new QGridLayout (this);

  l_prizes = new QLabel("Prize:", this);
  layout->addWidget (l_prizes, 0, 1);

  l_stacks = new QLabel("Stack:", this);
  layout->addWidget (l_stacks, 0, 3);

  l_values = new QLabel("Value:", this);
  layout->addWidget (l_values, 0, 4);

  l_per100s = new QLabel("Cent/Chip:", this);
  layout->addWidget (l_per100s, 0, 5);

  std::string hk[9] = { "q", "w", "e", "r", "t", "y", "u", "i", "o" };

  line_edit::reset_count ();
  for (int i = 0; i < 9; i++) {
    l_prize.append (new QLabel(this));
    if      (i == 0) l_prize.last ()->setText (QString::fromStdString(QVariant(i+1).toString ().toStdString ()+ "st (&" + hk[i] + "):"));
    else if (i == 2) l_prize.last ()->setText (QString::fromStdString(QVariant(i+1).toString ().toStdString () + "nd (&" + hk[i] + "):"));
    else             l_prize.last ()->setText (QString::fromStdString(QVariant(i+1).toString ().toStdString () + "rd (&" + hk[i] + "):"));
    layout->addWidget (l_prize.last (), i+1, 0);

    prizes.append (new line_edit(this));
    prizes.last ()->setValidator (new QDoubleValidator (this));
    layout->addWidget (prizes.last (), i+1, 1);
    if (i != 0) prizes.last ()->setEnabled (false);
    connect(prizes.last (), SIGNAL(text_edited(QString, int)), this, SLOT(manage_prizeedits(QString, int)));

    l_prize.last ()->setBuddy(prizes.at (i));
  }
  line_edit::reset_count ();
  for (int i = 0; i < 9; i++) {
    l_stack.append (new QLabel(this));
    l_stack.last ()->setText (QString::fromStdString("Player &" + QVariant(i+1).toString ().toStdString ()+ ":"));
    layout->addWidget (l_stack.last (), i+1, 2);

    stacks.append (new line_edit(this));
    stacks.last ()->setValidator (new QDoubleValidator (this));
    layout->addWidget (stacks.last (), i+1, 3);
    if (i != 0) stacks.last ()->setEnabled (false);
    connect(stacks.last (), SIGNAL(text_edited(QString, int)), this, SLOT(manage_stackedits(QString, int)));

    l_stack.last ()->setBuddy(stacks.at (i));
  } for (int i = 0; i < 9; i++) {
    l_value.append (new QLabel(this));
    l_value.last ()->setAlignment (Qt::AlignRight);
    layout->addWidget (l_value.last (), i+1, 4);
  } for (int i = 0; i < 9; i++) {
    l_per100.append (new QLabel(this));
    l_per100.last ()->setAlignment (Qt::AlignRight);
    layout->addWidget (l_per100.last (), i+1, 5);
  }

  b_calculate = new QPushButton ("&Calculate", this);
  layout->addWidget (b_calculate, 10, 0, 1, 6);
  connect (b_calculate, SIGNAL(clicked()), this, SLOT(calculate()));
}

void iicm_gui::manage_prizeedits(QString text, int num) {
  invalidate();
  if (text.isEmpty ()) {
    for (int i = num + 1; i < 9; i++)
      prizes.at (i)->setEnabled (false);
  } else if (num++ < 9) {
    prizes.at (num)->setEnabled (true);
    manage_prizeedits(prizes.at(num)->text (), num);
  }
}
void iicm_gui::manage_stackedits(QString text, int num) {
  invalidate();
  if (text.isEmpty ()) {
    for (int i = num + 1; i < 9; i++)
      stacks.at (i)->setEnabled (false);
  } else if (num++ < 9) {
    stacks.at (num)->setEnabled (true);
    manage_stackedits(stacks.at (num)->text (), num);
  }
}

void iicm_gui::invalidate() {
  for (int i = 0; i < 9; i++) {
    l_value.at (i)->clear ();
    l_per100.at (i)->clear ();
  }
}

float qstof (void* s) {
  return QVariant(((QLineEdit*) s)->text ()).toFloat ();
}

void iicm_gui::calculate () {

  float stack[9];
  int n_stacks;
  for (n_stacks = 0; n_stacks < 9; n_stacks++) {
    if (stacks.at (n_stacks)->text () == "") break;
    stack[n_stacks] = QVariant(stacks.at (n_stacks)->text ()).toFloat ();
  }

  float prize[9];
  int n_prizes;
  for (n_prizes = 0; n_prizes < 9; n_prizes++) {
    if (prizes.at (n_prizes)->text () == "") break;
    prize[n_prizes] = QVariant(prizes.at (n_prizes)->text ()).toFloat ();
  }

  /*int n_stacks;
  for (n_stacks = 0; n_stacks < 9; n_stacks++) if (stacks.at (n_stacks)->text () == "") break;
  float* stack = array_gather_f(n_stacks, &(stacks.at (0)), &(stacks.at (1)), &qstof);

  int n_prizes;
  for (n_prizes = 0; n_prizes < 9; n_prizes++) if (prizes.at (n_prizes)->text () == "") break;
  float* prize = array_gather_f(n_prizes, &(prize.at (0)), &(prize.at (1)), &qstof);*/

  float* results = calc_icm(n_stacks, stack, n_prizes, prize);
  for (int i = 0; i < n_stacks; i++) {
    l_value.at (i)->setText (QString("%1").QString::arg (results[i], 0, 'f', 2));
    l_per100.at (i)->setText (QString("%1").QString::arg ((results[i]*100)/stack[i], 0, 'f', 3));
  }

  //free (stack);
  //free (prize);
  free (results);
}

iicm_gui::~iicm_gui() {

}
