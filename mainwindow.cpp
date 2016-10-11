#include"mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect (ui->actionOpenFile, SIGNAL(triggered(bool)), this, SLOT(readFile()));
    connect(ui->actionLaxicalAnalyic, SIGNAL(triggered(bool)), this, SLOT(showToken()));
    connect(ui->code->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(on_line_number_verticalScrollbar_changed(int)));

    // set align of line_number text
    QTextCursor cursor = ui->line_number->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->line_number->setTextCursor(cursor);
}

void MainWindow::on_line_number_verticalScrollbar_changed(int value) {

//    ui->line_number->verticalScrollBar ()->setValue (value);
    QScrollBar* scrollbar = ui->line_number->verticalScrollBar ();
//     scrollbar->setSliderPosition(ui->code->verticalScrollBar ()->maximium ());
//    ui->code->verticalScrollBar ()->setMaximum (scrollbar->maximum ());
     scrollbar->setSliderPosition ((int)(value * 17.2));
     //     scrollbar->setValue (value);
     //     QMessageBox::about (this, "", QString::number (ui->code->verticalScrollBar ()->maximum ()) + ':' + QString::number (scrollbar->maximum ()));
     //     QMessageBox::about (this, "", QString::number (ui->code->verticalScrollBar ()->sliderPosition ()->maximum ()) + ':' + QString::number (scrollbar->maximum ()));
     }

     MainWindow::~MainWindow()
     {
         delete ui;
}

void MainWindow::readFile ()
{
    QString file_name = QFileDialog::getOpenFileName (this, tr("open file"), "", "", 0);
    if (!file_name.isNull ()) {
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

        QTextStream in(&file);
        while (!in.atEnd ()) {
            QString line = in.readLine ();
            ui->code->appendPlainText (line + '\n');
        }
    }
}

void MainWindow::showToken()
{

	Lexical::lexicalAnalyze (ui->code->toPlainText ());
	ui->token->setText (QString("row\tcol\ttoken\t\t\tvalue\t\n"));

	ui->error->setText ("----------------- ERROR LIST ------------------\n");

	auto tokens = Lexical::getTokens ();
	auto start = tokens.begin (), end = tokens.end ();

	while (start != end) {
		ui->token->append (QString("%1\t%2\t%3\t\t\t%4\t")
				.arg (start->getRow ())
				.arg (start->getColumn ())
				.arg (start->getToken ())
				.arg (start->getValue ()));
//		qDebug() << start->getColumn () << endl;
		++start;
	}

	auto errorStart = ErrorLog::getLexicalErrors ().begin ();
	auto errorEnd  = ErrorLog::getLexicalErrors ().end ();
	while (errorStart < errorEnd) {
		ui->error->append (*errorStart++);
	}
}

void MainWindow::on_code_textChanged()
{
//    QString text = ui->code->toPlainText ();
}

void MainWindow::on_code_blockCountChanged(int newBlockCount)
{
    int countCopy = newBlockCount, i = 1;
    while ((countCopy /= 10) > 0) { ++i; }

    QString tmp;
    for (int i = 1; i <= newBlockCount; ++i) {
        tmp += QString::number (i) + '\n';
    }
    ui->line_number->setText (tmp);

    ui->line_number->setFixedWidth (10 * i + 5);
    this->on_line_number_verticalScrollbar_changed (ui->code->verticalScrollBar ()->value ());
}
