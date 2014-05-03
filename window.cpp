#include "window.h"
#include "objeto.h"

#include <QtWidgets>

Window::Window() {
    setWindowTitle(tr("Elvis"));

    QGridLayout *mainLayout = new QGridLayout;
    menuBar = new QMenuBar();

    glArea = new GLWidget();

    // -------------------------------------
    // Substituir por uma só função (ou não)
    setupFileMenu();
    setupHelpMenu();
    // -------------------------------------
    createActions();
    createLeftBar();
    createBottomBar();

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(leftBar, 1, 0);
    mainLayout->addWidget(glArea, 1, 1);
    mainLayout->addWidget(bottomBar, 2, 0, 1, 2);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setRowStretch(2, 0);

    mostrarAcoesObjeto(true);

    setLayout(mainLayout);
}

void Window::createActions() {
    // -----------
    // Ferramentas
    // -----------
    addSelecionarAct = new QAction("Selecionar", this);
    addSelecionarAct->setShortcut(QKeySequence("S"));
    addPolilinhaAct = new QAction("Polilinha", this);
    addElipseAct = new QAction("Elipse", this);
    addElipseAct->setShortcut(QKeySequence("E"));
    addCirculoAct = new QAction("Círculo", this);
    addCirculoAct->setShortcut(QKeySequence("C"));
    addRetanguloAct = new QAction("Retângulo", this);
    addRetanguloAct->setShortcut(QKeySequence("R"));

    addSelecionarAct->setCheckable(true);
    addPolilinhaAct->setCheckable(true);
    addElipseAct->setCheckable(true);
    addCirculoAct->setCheckable(true);
    addRetanguloAct->setCheckable(true);

    addElipseAct->setChecked(true);

    // -------------------
    // Operações de objeto
    // -------------------
    transladarAct = new QAction("Translação", this);
    copiarAct = new QAction("Cópia", this);
    escalarAct = new QAction("Escalar", this);
    deslocarPtsAct = new QAction("Deslocar pontos", this);
    rotacionarAct = new QAction("Rotacionar", this);
    insertRemovePontoAct = new QAction("insertRemovePonto", this);

    copiarAct->setCheckable(true);
    transladarAct->setCheckable(true);
    rotacionarAct->setCheckable(true);
    escalarAct->setCheckable(true);
    deslocarPtsAct->setCheckable(true);
    insertRemovePontoAct->setCheckable(true);
}

void Window::mostrarAcoesObjeto(bool visivel) {
    if(visivel) {
        copiarAct->setVisible(true);
        transladarAct->setVisible(true);
        rotacionarAct->setVisible(true);
        escalarAct->setVisible(true);
        deslocarPtsAct->setVisible(true);
    } else {
        copiarAct->setVisible(false);
        transladarAct->setVisible(false);
        rotacionarAct->setVisible(false);
        escalarAct->setVisible(false);
        deslocarPtsAct->setVisible(false);
    }
}

void Window::createLeftBar() {
    leftBar = new QToolBar("Ferramentas principais");
    leftBar->setOrientation(Qt::Vertical);
    leftBar->setFloatable(false);
    leftBar->setMovable(false);

    QActionGroup* toolGroup = new QActionGroup(this);
    toolGroup->addAction(addSelecionarAct);
    toolGroup->addAction(addPolilinhaAct);
    toolGroup->addAction(addElipseAct);
    toolGroup->addAction(addCirculoAct);
    toolGroup->addAction(addRetanguloAct);

    toolGroup->addAction(copiarAct);
    toolGroup->addAction(transladarAct);
    toolGroup->addAction(rotacionarAct);
    toolGroup->addAction(escalarAct);
    toolGroup->addAction(deslocarPtsAct);
    toolGroup->addAction(insertRemovePontoAct);
    QObject::connect(toolGroup, SIGNAL(triggered(QAction*)), this, SLOT(setOperacao(QAction * )));

    leftBar->addAction(addSelecionarAct);
    leftBar->addAction(addPolilinhaAct);
    leftBar->addAction(addElipseAct);
    leftBar->addAction(addCirculoAct);
    leftBar->addAction(addRetanguloAct);

    leftBar->addAction(copiarAct);
    leftBar->addAction(transladarAct);
    leftBar->addAction(rotacionarAct);
    leftBar->addAction(escalarAct);
    leftBar->addAction(deslocarPtsAct);
    leftBar->addAction(insertRemovePontoAct);

}

void Window::createBottomBar() {
    bottomBar = new QToolBar();
    bottomBar->setOrientation(Qt::Horizontal);
    bottomBar->setFloatable(false);
    bottomBar->setMovable(false);

    QLabel* linhaColorLabel = new QLabel("Linha");
    linhaColorButton = new QToolButton();
    QColor* linhaColor = new QColor(Qt::black);
    QPixmap pxLinha(20, 20);
    pxLinha.fill(*linhaColor);
    linhaColorButton->setIcon(pxLinha);
    linhaColorButton->setAutoRaise(true);
    bottomBar->addWidget(linhaColorLabel);
    bottomBar->addWidget(linhaColorButton);
    QObject::connect(linhaColorButton, SIGNAL(clicked()), this, SLOT(setLinhaColor()));

    QLabel* fillColorLabel = new QLabel("Fill");
    fillColorButton = new QToolButton();
    QColor* fillColor = new QColor(Qt::red);
    QPixmap pxFill(20, 20);
    pxFill.fill(*fillColor);
    fillColorButton->setIcon(pxFill);
    fillColorButton->setAutoRaise(true);
    bottomBar->addWidget(fillColorLabel);
    bottomBar->addWidget(fillColorButton);
    QObject::connect(fillColorButton, SIGNAL(clicked()), this, SLOT(setFillColor()));

    bottomBar->addSeparator();

    QLabel* espessuraLinhaLabel = new QLabel("Espessura");
    QSpinBox* espessuraLinhaSpinBox = new QSpinBox();
    espessuraLinhaSpinBox->setSuffix(" px");
    espessuraLinhaSpinBox->setMinimum(1);
    espessuraLinhaSpinBox->setMaximum(50);
    espessuraLinhaSpinBox->setSingleStep(1);
    bottomBar->addWidget(espessuraLinhaLabel);
    bottomBar->addWidget(espessuraLinhaSpinBox);
    QObject::connect(espessuraLinhaSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setEspessuraLinha(int)));

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    bottomBar->addWidget(spacer);

    QSpinBox* zoomSpinBox = new QSpinBox();
    zoomSpinBox->setSuffix("%");
    zoomSpinBox->setMinimum(25);
    zoomSpinBox->setMaximum(1000);
    zoomSpinBox->setValue(100);
    zoomSpinBox->setSingleStep(5);
    bottomBar->addWidget(zoomSpinBox);
}

void Window::setupFileMenu() {
    QMenu *fileMenu = new QMenu(tr("&Arquivo"), this);
    menuBar->addMenu(fileMenu);

    fileMenu->addAction(tr("&Novo"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Abrir..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("&Sair"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void Window::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Ajuda"), this);
    menuBar->addMenu(helpMenu);

    helpMenu->addAction(tr("&Sobre"), this, SLOT(about()));
}

void Window::openFile(const QString &path) {
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Abrir arquivo"), "", ".elv");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            // Abre arquivo
        }
    }
}

void Window::about() {
    QMessageBox::about(this,
                       tr("Sobre Elvis"),
                       tr("Elvis é uma aplicação desenvolvida por Felipe Fernandes e Felipe Cortez para disciplina de Computação Gráfica na UFRN"));
}

void Window::newFile() {
    // Tratar criação de arquivo aqui
}

void Window::setOperacao(QAction* q) {
    if(q == addRetanguloAct) {
        glArea->forma = Objeto::RETANGULO;
        glArea->desenha = true;
    } else if(q == addCirculoAct) {
        glArea->forma = Objeto::CIRCULO;
        glArea->desenha = true;
    } else if(q->text() == "Polilinha") {
        glArea->forma = Objeto::POLILINHA;
        glArea->desenha = true;
    } else if(q->text() == "Elipse") {
        glArea->forma = Objeto::ELIPSE;
        glArea->desenha = true;
    } else if(q->text() == "Translação") {
        glArea->op = TRANSLACAO;
        glArea->desenha = false;
    } else if(q->text() == "Cópia") {
        glArea->op = COPIA;
        glArea->desenha = false;
    } else if(q->text() == "Escalar") {
        glArea->op = ESCALA;
        glArea->desenha = false;
    } else if(q->text() == "Deslocar pontos") {
        glArea->op = DESLOCARPONTOS;
        glArea->desenha = false;
    } else if(q->text() == "Rotacionar") {
        glArea->op = ROTACAO;
        glArea->desenha = false;
    } else if (q->text() == "insertRemovePonto"){
        glArea->op = INSERT_REMOVE_PONTO;
        glArea->desenha = false;
    }
    glArea->opBotaoDireito = false;
    glArea->descelecionaALL(); // sempre que uma opção (de desenho ou transformação) for escolhida, desselecione todos os objetos
}

void Window::setLinhaColor() {
    if(QApplication::keyboardModifiers() == Qt::ControlModifier) {
        QPixmap px(20, 20);
        QPainter *p = new QPainter(&px);
        px.fill(Qt::white);
        p->setBrush(Qt::red);
        p->setPen(QPen(Qt::red, 2));
        p->drawLine(QPoint(0, 20), QPoint(20, 0));
        delete p;
        linhaColorButton->setIcon(px);
        // linha pra false!
    } else {
        const QColor color =
                QColorDialog::getColor(QColor::fromRgbF(glArea->linhaColorSelecionada[0],
                                                        glArea->linhaColorSelecionada[1],
                                                        glArea->linhaColorSelecionada[2]),
                                                        this, "Selecionar cor");

        if (color.isValid()) {
            glArea->linhaColorSelecionada[0] = color.redF();
            glArea->linhaColorSelecionada[1] = color.greenF();
            glArea->linhaColorSelecionada[2] = color.blueF();

            QPixmap px(20, 20);
            px.fill(color);
            linhaColorButton->setIcon(px);
        }
    }
}

void Window::setFillColor() {
    if(QApplication::keyboardModifiers() == Qt::ControlModifier) {
        QPixmap px(20, 20);
        QPainter *p = new QPainter(&px);
        px.fill(Qt::white);
        p->setBrush(Qt::red);
        p->setPen(QPen(Qt::red, 2));
        p->drawLine(QPoint(0, 20), QPoint(20, 0));
        delete p;
        fillColorButton->setIcon(px);
        // preenchido pra false!
    } else {
        const QColor color =
                QColorDialog::getColor(QColor::fromRgbF(glArea->fillColorSelecionada[0],
                                                        glArea->fillColorSelecionada[1],
                                                        glArea->fillColorSelecionada[2]),
                                                        this, "Selecionar cor de fill");
        if (color.isValid()) {
            glArea->fillColorSelecionada[0] = color.redF();
            glArea->fillColorSelecionada[1] = color.greenF();
            glArea->fillColorSelecionada[2] = color.blueF();

            QPixmap px(20, 20);
            px.fill(color);
            fillColorButton->setIcon(px);
        }
    }
}

void Window::setEspessuraLinha(int espessura) {
    glArea->espessuraLinha = espessura;
}
