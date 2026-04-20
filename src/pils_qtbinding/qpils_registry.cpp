#include "registry.h"
namespace PILS
{
void QtObjectClassName::initialize()
{
    // const QtObjectClassName* classEntry = nullptr;

    // ===== QWidget =====
    BEGIN_CLASS(QWidget)
    CONSTRUCTOR_NOARGS(QWidget)
    CONSTRUCTOR_ARGS(QWidget, QWidget*)
    END_CLASS()

    // ===== QMainWindow =====
    BEGIN_CLASS(QMainWindow)
    CONSTRUCTOR_NOARGS(QMainWindow)
    CONSTRUCTOR_ARGS(QMainWindow, QWidget*)
    END_CLASS()

    // ===== QDialog =====
    BEGIN_CLASS(QDialog)
    CONSTRUCTOR_NOARGS(QDialog)
    CONSTRUCTOR_ARGS(QDialog, QWidget*)
    END_CLASS()

    // ===== QPushButton =====
    BEGIN_CLASS(QPushButton)
    CONSTRUCTOR_NOARGS(QPushButton)
    CONSTRUCTOR_ARGS(QPushButton, QWidget*)
    CONSTRUCTOR_ARGS(QPushButton, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QPushButton, const QString&)
    END_CLASS()

    // ===== QToolButton =====
    BEGIN_CLASS(QToolButton)
    CONSTRUCTOR_NOARGS(QToolButton)
    CONSTRUCTOR_ARGS(QToolButton, QWidget*)
    END_CLASS()

    // ===== QCheckBox =====
    BEGIN_CLASS(QCheckBox)
    CONSTRUCTOR_NOARGS(QCheckBox)
    CONSTRUCTOR_ARGS(QCheckBox, QWidget*)
    CONSTRUCTOR_ARGS(QCheckBox, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QCheckBox, const QString&)
    END_CLASS()

    // ===== QRadioButton =====
    BEGIN_CLASS(QRadioButton)
    CONSTRUCTOR_NOARGS(QRadioButton)
    CONSTRUCTOR_ARGS(QRadioButton, QWidget*)
    CONSTRUCTOR_ARGS(QRadioButton, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QRadioButton, const QString&)
    END_CLASS()

    // ===== QComboBox =====
    BEGIN_CLASS(QComboBox)
    CONSTRUCTOR_NOARGS(QComboBox)
    CONSTRUCTOR_ARGS(QComboBox, QWidget*)
    END_CLASS()

    // ===== QLineEdit =====
    BEGIN_CLASS(QLineEdit)
    CONSTRUCTOR_NOARGS(QLineEdit)
    CONSTRUCTOR_ARGS(QLineEdit, QWidget*)
    CONSTRUCTOR_ARGS(QLineEdit, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QLineEdit, const QString&)
    END_CLASS()

    // ===== QTextEdit =====
    BEGIN_CLASS(QTextEdit)
    CONSTRUCTOR_NOARGS(QTextEdit)
    CONSTRUCTOR_ARGS(QTextEdit, QWidget*)
    CONSTRUCTOR_ARGS(QTextEdit, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QTextEdit, const QString&)
    END_CLASS()

    // ===== QPlainTextEdit =====
    BEGIN_CLASS(QPlainTextEdit)
    CONSTRUCTOR_NOARGS(QPlainTextEdit)
    CONSTRUCTOR_ARGS(QPlainTextEdit, QWidget*)
    CONSTRUCTOR_ARGS(QPlainTextEdit, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QPlainTextEdit, const QString&)
    END_CLASS()

    // ===== QLabel =====
    BEGIN_CLASS(QLabel)
    CONSTRUCTOR_NOARGS(QLabel)
    CONSTRUCTOR_ARGS(QLabel, QWidget*)
    CONSTRUCTOR_ARGS(QLabel, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QLabel, const QString&)
    END_CLASS()

    // ===== QProgressBar =====
    BEGIN_CLASS(QProgressBar)
    CONSTRUCTOR_NOARGS(QProgressBar)
    CONSTRUCTOR_ARGS(QProgressBar, QWidget*)
    END_CLASS()

    // ===== QSlider =====
    BEGIN_CLASS(QSlider)
    CONSTRUCTOR_NOARGS(QSlider)
    CONSTRUCTOR_ARGS(QSlider, QWidget*)
    CONSTRUCTOR_ARGS(QSlider, Qt::Orientation, QWidget*)
    CONSTRUCTOR_ARGS(QSlider, Qt::Orientation)
    END_CLASS()

    // ===== QSpinBox =====
    BEGIN_CLASS(QSpinBox)
    CONSTRUCTOR_NOARGS(QSpinBox)
    CONSTRUCTOR_ARGS(QSpinBox, QWidget*)
    END_CLASS()

    // ===== QDoubleSpinBox =====
    BEGIN_CLASS(QDoubleSpinBox)
    CONSTRUCTOR_NOARGS(QDoubleSpinBox)
    CONSTRUCTOR_ARGS(QDoubleSpinBox, QWidget*)
    END_CLASS()

    // ===== QTabWidget =====
    BEGIN_CLASS(QTabWidget)
    CONSTRUCTOR_NOARGS(QTabWidget)
    CONSTRUCTOR_ARGS(QTabWidget, QWidget*)
    END_CLASS()

    // ===== QSplitter =====
    BEGIN_CLASS(QSplitter)
    CONSTRUCTOR_NOARGS(QSplitter)
    CONSTRUCTOR_ARGS(QSplitter, QWidget*)
    CONSTRUCTOR_ARGS(QSplitter, Qt::Orientation, QWidget*)
    CONSTRUCTOR_ARGS(QSplitter, Qt::Orientation)
    END_CLASS()

    // ===== QMenu =====
    BEGIN_CLASS(QMenu)
    CONSTRUCTOR_NOARGS(QMenu)
    CONSTRUCTOR_ARGS(QMenu, QWidget*)
    CONSTRUCTOR_ARGS(QMenu, const QString&, QWidget*)
    CONSTRUCTOR_ARGS(QMenu, const QString&)
    END_CLASS()

    // ===== QAction =====
    BEGIN_CLASS(QAction)
    CONSTRUCTOR_NOARGS(QAction)
    CONSTRUCTOR_ARGS(QAction, QObject*)
    CONSTRUCTOR_ARGS(QAction, const QString&, QObject*)
    CONSTRUCTOR_ARGS(QAction, const QString&)
    END_CLASS()

    // ===== QFileDialog =====
    BEGIN_CLASS(QFileDialog)
    CONSTRUCTOR_NOARGS(QFileDialog)
    CONSTRUCTOR_ARGS(QFileDialog, QWidget*)
    CONSTRUCTOR_ARGS(QFileDialog, QWidget*, const QString&)
    CONSTRUCTOR_ARGS(QFileDialog, QWidget*, const QString&, const QString&)
    END_CLASS()

    // ===== QMessageBox =====
    BEGIN_CLASS(QMessageBox)
    CONSTRUCTOR_NOARGS(QMessageBox)
    CONSTRUCTOR_ARGS(QMessageBox, QWidget*)
    END_CLASS()

    // ===== Views =====
    BEGIN_CLASS(QListView)
    CONSTRUCTOR_NOARGS(QListView)
    CONSTRUCTOR_ARGS(QListView, QWidget*)
    END_CLASS()

    BEGIN_CLASS(QTreeView)
    CONSTRUCTOR_NOARGS(QTreeView)
    CONSTRUCTOR_ARGS(QTreeView, QWidget*)
    END_CLASS()

    BEGIN_CLASS(QTableView)
    CONSTRUCTOR_NOARGS(QTableView)
    CONSTRUCTOR_ARGS(QTableView, QWidget*)
    END_CLASS()
}

void QtMethodName::initialize()
    {
        // QWidget basics
        IMPLEMENT(QWidget, show)
        IMPLEMENT(QWidget, hide)
        IMPLEMENT(QWidget, close)
        IMPLEMENT_OVERLOAD(QWidget, update, void(QWidget::*)())
        IMPLEMENT_OVERLOAD(QWidget, repaint, void(QWidget::*)())

        IMPLEMENT(QWidget, width)
        IMPLEMENT(QWidget, height)
        IMPLEMENT(QWidget, size)
        IMPLEMENT(QWidget, pos)

        IMPLEMENT(QWidget, setWindowTitle)
        IMPLEMENT(QWidget, windowTitle)

        IMPLEMENT(QWidget, setEnabled)
        IMPLEMENT(QWidget, isEnabled)

        IMPLEMENT(QWidget, setVisible)
        IMPLEMENT(QWidget, isVisible)

        IMPLEMENT(QWidget, setStyleSheet)

        IMPLEMENT(QWidget, setWindowIcon)

        IMPLEMENT_OVERLOAD(QWidget, setFocus, void(QWidget::*)())

        IMPLEMENT_OVERLOAD(QWidget, resize, void(QWidget::*)(int,int))
        // IMPLEMENT_OVERLOAD(QWidget, resize, void(QWidget::*)(const QSize&))

        IMPLEMENT_OVERLOAD(QWidget, move, void(QWidget::*)(int,int))

        IMPLEMENT_OVERLOAD(QWidget, setGeometry, void(QWidget::*)(int,int,int,int))

        // Layout-ish
        IMPLEMENT(QWidget, setLayout)
        IMPLEMENT(QWidget, layout)

        // QMainWindow
        IMPLEMENT(QMainWindow, setCentralWidget)
        IMPLEMENT(QMainWindow, centralWidget)

        IMPLEMENT(QMainWindow, menuBar)
        IMPLEMENT(QMainWindow, statusBar)
        IMPLEMENT_OVERLOAD(QMainWindow, addToolBar, QToolBar*(QMainWindow::*)(const QString&))

        // QDialog
        IMPLEMENT(QDialog, exec)
        IMPLEMENT(QDialog, accept)
        IMPLEMENT(QDialog, reject)

        // QText / PlainText
        IMPLEMENT(QPlainTextEdit, setPlainText)
        IMPLEMENT(QPlainTextEdit, toPlainText)
        IMPLEMENT(QPlainTextEdit, appendPlainText)
        IMPLEMENT(QPlainTextEdit, clear)
        IMPLEMENT(QPlainTextEdit, setReadOnly)

        IMPLEMENT(QTextEdit, setText)
        IMPLEMENT(QTextEdit, toPlainText)
        IMPLEMENT(QTextEdit, setHtml)
        IMPLEMENT(QTextEdit, toHtml)
        IMPLEMENT(QTextEdit, clear)

        // QLineEdit
        IMPLEMENT(QLineEdit, setText)
        IMPLEMENT(QLineEdit, text)
        IMPLEMENT(QLineEdit, clear)
        IMPLEMENT(QLineEdit, setPlaceholderText)

        // QLabel
        IMPLEMENT(QLabel, setText)
        IMPLEMENT(QLabel, text)
        IMPLEMENT(QLabel, setPixmap)

        // QPushButton
        IMPLEMENT(QPushButton, setText)
        IMPLEMENT(QPushButton, text)
        IMPLEMENT(QPushButton, setEnabled)
        IMPLEMENT(QPushButton, click)

        // QCheckBox / QRadioButton
        IMPLEMENT(QCheckBox, setChecked)
        IMPLEMENT(QCheckBox, isChecked)

        IMPLEMENT(QRadioButton, setChecked)
        IMPLEMENT(QRadioButton, isChecked)

        // QComboBox
        IMPLEMENT_OVERLOAD(QComboBox, addItem, void(QComboBox::*)(const QString&, const QVariant&))
        IMPLEMENT(QComboBox, currentText)
        IMPLEMENT(QComboBox, setCurrentIndex)
        IMPLEMENT(QComboBox, currentIndex)

        // QProgressBar
        IMPLEMENT(QProgressBar, setValue)
        IMPLEMENT(QProgressBar, value)
        IMPLEMENT(QProgressBar, setRange)

        // QFileDialog (statics er tricky – kun hvis du wrapper dem)
        // IMPLEMENT(QFileDialog, getOpenFileName)

        // QMessageBox
        IMPLEMENT(QMessageBox, setText)
        IMPLEMENT(QMessageBox, exec)

        // QTimer
        IMPLEMENT_OVERLOAD(QTimer, start, void(QTimer::*)(int))
        IMPLEMENT(QTimer, stop)
        IMPLEMENT_OVERLOAD(QTimer, setInterval, void(QTimer::*)(int))

        // QSplitter
        IMPLEMENT(QSplitter, addWidget)
        IMPLEMENT(QSplitter, setOrientation)

        // QTabWidget
        IMPLEMENT_OVERLOAD(QTabWidget, addTab, int(QTabWidget::*)(QWidget*, const QString&))
        IMPLEMENT(QTabWidget, setCurrentIndex)
        IMPLEMENT(QTabWidget, currentIndex)

        // QStackedWidget
        IMPLEMENT(QStackedWidget, addWidget)
        IMPLEMENT(QStackedWidget, setCurrentIndex)
        IMPLEMENT(QStackedWidget, currentIndex)
    }

void QtSignalName::initialize()
{
    // QWidget basis
    SIGNAL_IMPLEMENT(QWidget, customContextMenuRequested)
    SIGNAL_IMPLEMENT(QWidget, windowTitleChanged)
    SIGNAL_IMPLEMENT(QWidget, windowIconChanged)
    SIGNAL_IMPLEMENT(QWidget, windowIconTextChanged)
    SIGNAL_IMPLEMENT(QWidget, destroyed)

    // visibility / lifecycle
    SIGNAL_IMPLEMENT(QWidget, show)
    SIGNAL_IMPLEMENT(QWidget, hide)

    SIGNAL_IMPLEMENT(QPushButton, clicked)
    SIGNAL_IMPLEMENT(QPushButton, pressed)
    SIGNAL_IMPLEMENT(QPushButton, released)
    SIGNAL_IMPLEMENT(QPushButton, toggled)

    SIGNAL_IMPLEMENT(QLineEdit, textChanged)
    SIGNAL_IMPLEMENT(QLineEdit, textEdited)
    SIGNAL_IMPLEMENT(QLineEdit, returnPressed)
    SIGNAL_IMPLEMENT(QLineEdit, editingFinished)
    SIGNAL_IMPLEMENT(QLineEdit, cursorPositionChanged)
    SIGNAL_IMPLEMENT(QLineEdit, selectionChanged)

    SIGNAL_IMPLEMENT(QTextEdit, textChanged)
    SIGNAL_IMPLEMENT(QTextEdit, cursorPositionChanged)
    SIGNAL_IMPLEMENT(QTextEdit, selectionChanged)

    SIGNAL_IMPLEMENT(QPlainTextEdit, textChanged)
    SIGNAL_IMPLEMENT(QPlainTextEdit, cursorPositionChanged)
    SIGNAL_IMPLEMENT(QPlainTextEdit, selectionChanged)
    SIGNAL_IMPLEMENT(QPlainTextEdit, updateRequest)
    SIGNAL_IMPLEMENT(QPlainTextEdit, blockCountChanged)

    SIGNAL_IMPLEMENT(QComboBox, currentIndexChanged)
    SIGNAL_IMPLEMENT(QComboBox, currentTextChanged)

    SIGNAL_IMPLEMENT(QComboBox, activated)
    SIGNAL_IMPLEMENT(QComboBox, highlighted)
    SIGNAL_IMPLEMENT(QComboBox, editTextChanged)

    SIGNAL_IMPLEMENT(QCheckBox, checkStateChanged)
    SIGNAL_IMPLEMENT(QCheckBox, toggled)

    SIGNAL_IMPLEMENT(QRadioButton, toggled)

    SIGNAL_IMPLEMENT(QSlider, valueChanged)
    SIGNAL_IMPLEMENT(QSlider, sliderPressed)
    SIGNAL_IMPLEMENT(QSlider, sliderReleased)
    SIGNAL_IMPLEMENT(QSlider, sliderMoved)

    SIGNAL_IMPLEMENT(QSpinBox, valueChanged)
    SIGNAL_IMPLEMENT(QDoubleSpinBox, valueChanged)

    SIGNAL_IMPLEMENT(QTabWidget, currentChanged)
    SIGNAL_IMPLEMENT(QTabWidget, tabCloseRequested)
    SIGNAL_IMPLEMENT(QTabWidget, tabBarClicked)
    SIGNAL_IMPLEMENT(QTabWidget, tabBarDoubleClicked)

    SIGNAL_IMPLEMENT(QSplitter, splitterMoved)

    SIGNAL_IMPLEMENT(QMainWindow, iconSizeChanged)
    SIGNAL_IMPLEMENT(QMainWindow, toolButtonStyleChanged)
    SIGNAL_IMPLEMENT(QMainWindow, tabifiedDockWidgetActivated)

    SIGNAL_IMPLEMENT(QAction, triggered)
    SIGNAL_IMPLEMENT(QAction, toggled)
    SIGNAL_IMPLEMENT(QAction, hovered)
    SIGNAL_IMPLEMENT(QAction, changed)

    SIGNAL_IMPLEMENT(QMenu, triggered)
    SIGNAL_IMPLEMENT(QMenu, hovered)
    SIGNAL_IMPLEMENT(QMenu, aboutToShow)
    SIGNAL_IMPLEMENT(QMenu, aboutToHide)

    SIGNAL_IMPLEMENT(QApplication, focusChanged)
    SIGNAL_IMPLEMENT(QApplication, applicationStateChanged)
    SIGNAL_IMPLEMENT(QApplication, aboutToQuit)

    SIGNAL_IMPLEMENT(QScrollBar, valueChanged)
    SIGNAL_IMPLEMENT(QScrollBar, sliderMoved)
    SIGNAL_IMPLEMENT(QScrollBar, rangeChanged)

    SIGNAL_IMPLEMENT(QListView, clicked)
    SIGNAL_IMPLEMENT(QListView, doubleClicked)
    SIGNAL_IMPLEMENT(QListView, activated)

    SIGNAL_IMPLEMENT(QTreeView, clicked)
    SIGNAL_IMPLEMENT(QTreeView, doubleClicked)
    SIGNAL_IMPLEMENT(QTreeView, expanded)
    SIGNAL_IMPLEMENT(QTreeView, collapsed)

    SIGNAL_IMPLEMENT(QWindow, visibleChanged)
    SIGNAL_IMPLEMENT(QWindow, widthChanged)
    SIGNAL_IMPLEMENT(QWindow, heightChanged)
    SIGNAL_IMPLEMENT(QWindow, xChanged)
    SIGNAL_IMPLEMENT(QWindow, yChanged)
}
}
