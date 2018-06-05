#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CodeEditor.h"
#include "Scanner.h"
#include<fstream>

#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QFileInfo>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->editorTabWidget->addTab(new CodeEditor(),"new file");

   // QDebugStream qout(std::cout, ui->Console);
    //std::cout << "Send this to the Text Edit!" << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_File_triggered()
{
    ui->editorTabWidget->addTab(new CodeEditor(),"new file");
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fullPath = QFileDialog::getOpenFileName(this, "Open the file");


    QFileInfo fileInfo(fullPath);
    QString filename(fileInfo.fileName());

    CodeEditor* codeEditor = new CodeEditor(fullPath);
    ui->editorTabWidget->addTab(codeEditor,filename);
	ui->editorTabWidget->setCurrentWidget(codeEditor);
}

void MainWindow::on_editorTabWidget_tabCloseRequested(int index)
{
    this->on_actionSave_triggered();
    ui->editorTabWidget->removeTab(index);
}

void MainWindow::on_actionSave_triggered()
{
    CodeEditor * curEditor = dynamic_cast<CodeEditor *>(ui->editorTabWidget->currentWidget());
    curEditor->saveToFile();
    setCurrentEditorTabTitle(curEditor->getFilePath());
}

void MainWindow::on_actionLexical_Analysis_triggered()
{
    CodeEditor * curEditor = dynamic_cast<CodeEditor *>(ui->editorTabWidget->currentWidget());
    curEditor->saveToFile();
    QString filePath = curEditor->getFilePath();
    setCurrentEditorTabTitle(filePath);
    std::ifstream* infile = new std::ifstream();
    infile->open(filePath.toStdString());
    Scanner scanner(*infile);
	ui->CompileOutput->append("Lexical Analysis result:\n");
    std::list<Token> tokenSequence = scanner.getTokenSequence();
    for(auto& token:tokenSequence){
        ui->CompileOutput->append(token.toString().c_str());
    }
}

void MainWindow::setCurrentEditorTabTitle(QString filePath)
{
    if(!filePath.isEmpty()){
        QFileInfo fileInfo(filePath);
        QString fileName(fileInfo.fileName());
        ui->editorTabWidget->setTabText(ui->editorTabWidget->currentIndex(),fileName);
    }
}

