#ifndef IICM_GUI_H
#define IICM_GUI_H

#include <QDialog>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class line_edit : public QLineEdit {
  Q_OBJECT
  public:
    line_edit(QWidget* _parent = 0) : QLineEdit::QLineEdit(_parent) {
      _i = _n;
      _n++;
      connect(this, SIGNAL(textEdited(QString)), this, SLOT(emit_text_edited(QString)));
    }
  static void reset_count() { _n = 0; }
  signals:
    void focus_in(int _i);
    void focus_out(int _i);
    //void editing_finished_str(QString text, int num);
    void text_edited(QString text, int num);
  public slots:
    //void emit_editing_finished_str() { emit editing_finished_str_num(this->text (), _i); }
    void emit_text_edited(QString _text) { emit text_edited(_text, _i); }
  protected:
    void focusInEvent(QFocusEvent * _event) { QLineEdit::focusInEvent (_event); emit focus_in(_i); }
    void focusOutEvent(QFocusEvent * _event) { QLineEdit::focusOutEvent (_event); emit focus_out(_i); }
  private:
    int _i;
    static int _n;
};

class iicm_gui : public QDialog {
  Q_OBJECT
  public:
    iicm_gui();
    ~iicm_gui();
  signals:
  public slots:
    void invalidate ();
    void calculate ();
    //void manage_edits(QString text, QWidget* parent, int num);
    void manage_prizeedits(QString text, int num);
    void manage_stackedits(QString text, int num);
  private:
    QGridLayout* layout;
    QVector<line_edit*> prizes;
    QVector<line_edit*> stacks;
    QVector<QLabel*> l_stack;
    QVector<QLabel*> l_prize;
    QLabel* l_stacks;
    QLabel* l_prizes;
    QPushButton* b_calculate;
    QVector<QLabel*> l_value;
    QVector<QLabel*> l_per100;
    QLabel* l_values;
    QLabel* l_per100s;
  //
};

float qstof (void* s);

#endif // IICM_GUI_H
