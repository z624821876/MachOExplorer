#ifndef HEXDUMPWIDGET_H
#define HEXDUMPWIDGET_H

#include <QWidget>
#include <array>
#include <memory>

#include <QDebug>
#include <QTextEdit>
#include <QDockWidget>
#include <QMouseEvent>



namespace Ui {
class HexdumpWidget;
}

class HexdumpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HexdumpWidget(QWidget *parent = 0);
    ~HexdumpWidget();

    void setAddressAs64Bit(bool is64bit){ m_isAddr64bit = is64bit;}

    void loadAddress(unsigned long long displayOffset,unsigned long long addr,unsigned long long len);
    void selectRange(unsigned long long addr,unsigned long long len);

private:

    void setupFont();
    void setupColors();
    void updateHeaders();
    void setupScrollSync();
    void setupSelection();

private slots:

    void selectionChanged();

protected:
    void showEvent(QShowEvent *event);
private:

    void refresh();

    std::array<QString, 3> fetchHexdump();
    void updateWidths();
    unsigned long long hexPositionToAddress(int position);
    int asciiAddressToPosition(unsigned long long address);
    void setTextEditPosition(QTextEdit *textEdit, int position);
    unsigned long long asciiPositionToAddress(int position);
    int hexAddressToPosition(unsigned long long address);

private:
    unsigned long long m_displayOffset = 0;
    unsigned long long m_addr = 0;
    unsigned long long m_length = 0;
    unsigned long long m_columnCount = 16;
    bool m_isAddr64bit = true;

private:
    Ui::HexdumpWidget *ui;
};

#endif // HEXDUMPWIDGET_H
