using Avalonia.Controls;
using Avalonia.Controls.Shapes;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.VisualTree;
using ShemaPaint.Models;
using ShemaPaint.ViewModels;
using ShemaPaint.Views.ChildWindows;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;

namespace ShemaPaint.Views
{
    public partial class MainWindow : Window
    {
        private Avalonia.Point pointPointPresed;
        private Avalonia.Point pointPosInBorder;
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainWindowViewModel(this);
            AddHandler(DragDrop.DropEvent, Drop);
        }

        private void PointPresedOn(object sender, PointerPressedEventArgs pointerPressedEventArgs)
        {
            pointPointPresed = pointerPressedEventArgs
                .GetPosition(
                this.GetVisualDescendants()
                .OfType<Canvas>()
                .FirstOrDefault());
            if (this.DataContext is MainWindowViewModel viewModel)
            {
                if (viewModel.EventMove == false)
                {
                    if (viewModel.EventClass == true)
                    {
                        viewModel.ElementColection.Add(new El_Class
                        {
                            StartPoint = new Avalonia.Point(
                                            pointPointPresed.X - 10,
                                            pointPointPresed.Y - 10),
                            Width = 100,
                            Height = 100,
                            FontSizeMain = 10,
                            FontSizeAt = 10,
                            FontSizeOp = 10,
                        });
                    }
                    else if (viewModel.EventInterface == true)
                    {
                        viewModel.ElementColection.Add(new El_Interface
                        {
                            StartPoint = new Avalonia.Point(
                                            pointPointPresed.X - 10,
                                            pointPointPresed.Y - 10),
                            Width = 100,
                            Height = 100,
                            FontSizeMain = 10,
                            FontSizeAt = 10,
                            FontSizeOp = 10,
                        });
                    }
                    else if (viewModel.EventLine == true)
                    {

                        if (pointerPressedEventArgs.Source is Avalonia.Controls.Shapes.Ellipse ellipse)
                        {
                            if (viewModel.LineNasled == true)
                            {
                                if (ellipse.DataContext is El_Class classElement)
                                {
                                    viewModel.ElementColection.Add(new LineNasled
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstClass = classElement,
                                    });
                                }
                                else if (ellipse.DataContext is El_Interface interfaceElement)
                                {
                                    viewModel.ElementColection.Add(new LineNasled
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstInterface = interfaceElement,
                                    });
                                }
                                this.PointerMoved += PointerMoveDrawLine;
                                this.PointerReleased += PointerPressedReleasedDrawLine;
                            }
                            else if (viewModel.LineRealiz == true)
                            {
                                if (ellipse.DataContext is El_Class classElement)
                                {
                                    viewModel.ElementColection.Add(new LineRealiz
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstClass = classElement,
                                    });
                                }
                                else if (ellipse.DataContext is El_Interface interfaceElement)
                                {
                                    viewModel.ElementColection.Add(new LineRealiz
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstInterface = interfaceElement,
                                    });
                                }
                                this.PointerMoved += PointerMoveDrawLine;
                                this.PointerReleased += PointerPressedReleasedDrawLine;
                            }
                            else if (viewModel.LineZavis == true)
                            {
                                if (ellipse.DataContext is El_Class classElement)
                                {
                                    viewModel.ElementColection.Add(new LineZavis
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstClass = classElement,
                                    });
                                }
                                else if (ellipse.DataContext is El_Interface interfaceElement)
                                {
                                    viewModel.ElementColection.Add(new LineZavis
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstInterface = interfaceElement,
                                    });
                                }
                                this.PointerMoved += PointerMoveDrawLine;
                                this.PointerReleased += PointerPressedReleasedDrawLine;
                            }
                            else if (viewModel.LineAgreg == true)
                            {
                                if (ellipse.DataContext is El_Class classElement)
                                {
                                    viewModel.ElementColection.Add(new LineAgreg
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstClass = classElement,
                                    });
                                }
                                else if (ellipse.DataContext is El_Interface interfaceElement)
                                {
                                    viewModel.ElementColection.Add(new LineAgreg
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstInterface = interfaceElement,
                                    });
                                }
                                this.PointerMoved += PointerMoveDrawLine;
                                this.PointerReleased += PointerPressedReleasedDrawLine;
                            }
                            else if (viewModel.LineCompos == true)
                            {
                                if (ellipse.DataContext is El_Class classElement)
                                {
                                    viewModel.ElementColection.Add(new LineCompos
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstClass = classElement,
                                    });
                                }
                                else if (ellipse.DataContext is El_Interface interfaceElement)
                                {
                                    viewModel.ElementColection.Add(new LineCompos
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstInterface = interfaceElement,
                                    });
                                }
                                this.PointerMoved += PointerMoveDrawLine;
                                this.PointerReleased += PointerPressedReleasedDrawLine;
                            }
                            else if (viewModel.LineAsoc == true)
                            {
                                if (ellipse.DataContext is El_Class classElement)
                                {
                                    viewModel.ElementColection.Add(new LineAsoc
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstClass = classElement,
                                    });
                                }
                                else if (ellipse.DataContext is El_Interface interfaceElement)
                                {
                                    viewModel.ElementColection.Add(new LineAsoc
                                    {
                                        StartPoint = pointPointPresed,
                                        EndPoint = pointPointPresed,
                                        FirstInterface = interfaceElement,
                                    });
                                }
                                this.PointerMoved += PointerMoveDrawLine;
                                this.PointerReleased += PointerPressedReleasedDrawLine;
                            }
                        }
                    }
                }
                else if (viewModel.EventMove == true)
                {
                    if (pointerPressedEventArgs.Source is Avalonia.Controls.Shapes.Rectangle rect)
                    {
                        pointPosInBorder = pointerPressedEventArgs.GetPosition(rect);
                        this.PointerMoved += PointerMoveDragBorder;
                        this.PointerReleased += PointerRelesDragBorder;
                    }
                }

            }
        }

        private void PointerMoveDragBorder(object? sender, PointerEventArgs pointerEventArgs)
        {
            if (pointerEventArgs.Source is Avalonia.Controls.Shapes.Rectangle rect)
            {
                Avalonia.Point curentPointerPosition = pointerEventArgs
                    .GetPosition(
                    this.GetVisualDescendants()
                    .OfType<Canvas>()
                    .FirstOrDefault());
                if (rect.DataContext is El_Class clas)
                {
                    clas.StartPoint = new Avalonia.Point(
                        curentPointerPosition.X - pointPosInBorder.X,
                        curentPointerPosition.Y - pointPosInBorder.Y);
                }
                else if (rect.DataContext is El_Interface interf)
                {
                    interf.StartPoint = new Avalonia.Point(
                        curentPointerPosition.X - pointPosInBorder.X,
                        curentPointerPosition.Y - pointPosInBorder.Y);
                }
            }
        }
        private void PointerRelesDragBorder(object? sender, PointerReleasedEventArgs pREA)
        {
            this.PointerMoved -= PointerMoveDragBorder;
            this.PointerReleased -= PointerRelesDragBorder;
        }

        private void PointerMoveDrawLine(object? sender, PointerEventArgs pointerEventArgs)
        {
            if (this.DataContext is MainWindowViewModel mwvm)
            {
                Debug.WriteLine(sender);
                ILines? lineElements = mwvm.ElementColection[mwvm.ElementColection.Count - 1] as ILines;
                if (lineElements != null)
                {
                    Avalonia.Point curentPointPos = pointerEventArgs
                        .GetPosition(
                        this.GetVisualDescendants()
                        .OfType<Canvas>()
                        .FirstOrDefault());
                    lineElements.EndPoint = new Avalonia.Point(
                        curentPointPos.X - 1,
                        curentPointPos.Y - 1);
                }
            }
        }
        private void PointerPressedReleasedDrawLine(object? sender, PointerReleasedEventArgs pointerReleasedEventArgs)
        {
            this.PointerMoved -= PointerMoveDrawLine;
            this.PointerReleased -= PointerPressedReleasedDrawLine;
            var canvas = this.GetVisualDescendants()
                .OfType<Canvas>()
                .FirstOrDefault(canvas => string.IsNullOrEmpty(canvas.Name) == false &&
                canvas.Name.Equals("realCanvas"));
            var coords = pointerReleasedEventArgs.GetPosition(canvas);
            var element = canvas.InputHitTest(coords);
            MainWindowViewModel mwvm = this.DataContext as MainWindowViewModel;
            if (element is Ellipse ellipse)
            {
                if (ellipse.DataContext is El_Class classElement)
                {
                    ILines line = mwvm.ElementColection[mwvm.ElementColection.Count - 1] as ILines;
                    if (line.FirstClass != classElement)
                    {
                        line.SecondClass = classElement;
                        line.PathUpdate();
                        return;
                    }
                }
                if (ellipse.DataContext is El_Interface interfaceElement)
                {
                    ILines line = mwvm.ElementColection[mwvm.ElementColection.Count - 1] as ILines;
                    if (line.FirstInterface != interfaceElement)
                    {
                        line.SecondInterface = interfaceElement;
                        line.PathUpdate();
                        return;
                    }
                }
            }
            mwvm.ElementColection.RemoveAt(mwvm.ElementColection.Count - 1);
        }

        private void DoubleTap(object sender, RoutedEventArgs e)
        {
            if (DataContext is MainWindowViewModel mwvm)
            {
                var src = e.Source;
                if (src == null) return;

                var name = src.GetType().Name;
                if (name == "Rectangle")
                {
                    El_Class? elementClass = null;
                    El_Interface? elementInterface = null;
                    if (e.Source is Avalonia.Controls.Shapes.Rectangle rect)
                    {
                        if (rect.DataContext is El_Class rectClass)
                        {
                            elementClass = rectClass;
                        }
                        else if (rect.DataContext is El_Interface rectInterface)
                        {
                            elementInterface = rectInterface;
                        }
                    }

                    if (mwvm.EventChangeOption == true)
                    {
                        ChangeOption? optionWindow = null;
                        if (elementClass != null) optionWindow = new ChangeOption(elementClass);
                        else if (elementInterface != null) optionWindow = new ChangeOption(elementInterface);
                        optionWindow.ShowDialog(this);
                    }
                    else if (mwvm.EventChangeForm == true)
                    {
                        ChangeFormWindow? changeFormWindow = null;
                        if (elementClass != null) changeFormWindow = new ChangeFormWindow(elementClass);
                        else if (elementInterface != null) changeFormWindow = new ChangeFormWindow(elementInterface);
                        changeFormWindow.ShowDialog(this);
                    }
                    else if (mwvm.EventDelete == true)
                    {
                        ObservableCollection<IFigures> tempColection = mwvm.ElementColection;
                        for (int i = mwvm.ElementColection.Count - 1; i >= 0; i--)
                        {
                            if (elementClass != null)
                            {
                                if (tempColection[i] is El_Class tempCLass)
                                {
                                    if (tempCLass == elementClass)
                                    {
                                        mwvm.ElementColection.RemoveAt(i);
                                        break;
                                    }
                                }
                                else if (tempColection[i] is ILines tempLines)
                                {
                                    if (tempLines.FirstClass != null)
                                    {
                                        if (tempLines.FirstClass == elementClass)
                                        {
                                            mwvm.ElementColection.RemoveAt(i);
                                        }
                                    }
                                    if (tempLines.SecondClass != null)
                                    {
                                        if (tempLines.SecondClass == elementClass)
                                        {
                                            mwvm.ElementColection.RemoveAt(i);
                                        }
                                    }
                                }
                            }
                            else if (elementInterface != null)
                            {
                                if (tempColection[i] is El_Interface tempInterface)
                                {
                                    if (tempInterface == elementInterface)
                                    {
                                        mwvm.ElementColection.RemoveAt(i);
                                        break;
                                    }
                                }
                                else if (tempColection[i] is ILines tempLines)
                                {
                                    if (tempLines.FirstInterface != null)
                                    {
                                        if (tempLines.FirstInterface == elementInterface)
                                        {
                                            mwvm.ElementColection.RemoveAt(i);
                                        }
                                    }
                                    if (tempLines.SecondInterface != null)
                                    {
                                        if (tempLines.SecondInterface == elementInterface)
                                        {
                                            mwvm.ElementColection.RemoveAt(i);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private async void OpenSaveMenu(object sender, RoutedEventArgs eventArgs)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "all files",
                Extensions = new string[] { }.ToList()
            });
            saveFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "png files",
                Extensions = new string[] { "png" }.ToList()
            });
            saveFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "xml files",
                Extensions = new string[] { "xml" }.ToList()
            });
            saveFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "json files",
                Extensions = new string[] { "json" }.ToList()
            });
            saveFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "yaml files",
                Extensions = new string[] { "yaml" }.ToList()
            });
            string? path = await saveFileDialog.ShowAsync(this);
            if (path != null)
            {
                if (this.DataContext is MainWindowViewModel viewModel)
                {
                    viewModel.SaveColection(path);
                }
            }
        }

        private async void OpenLoadMenu(object sender, RoutedEventArgs eventArgs)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "all files",
                Extensions = new string[] { }.ToList()
            });
            openFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "xml files",
                Extensions = new string[] { "xml" }.ToList()
            });
            openFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "json files",
                Extensions = new string[] { "json" }.ToList()
            });
            openFileDialog.Filters.Add(new FileDialogFilter
            {
                Name = "yaml files",
                Extensions = new string[] { "yaml" }.ToList()
            });
            string[]? path = await openFileDialog.ShowAsync(this);
            if (path != null)
            {
                if (this.DataContext is MainWindowViewModel viewModel)
                {
                    viewModel.LoadColection(path[0]);
                }
            }
        }

        private void Drop(object? sender, DragEventArgs dragEventArgs)
        {
            if (dragEventArgs.Data.Contains(DataFormats.FileNames) == true)
            {
                string? filePath = dragEventArgs.Data.GetFileNames()?.FirstOrDefault();
                if (filePath != null)
                {
                    if (this.DataContext is MainWindowViewModel viewModel)
                    {
                        viewModel.LoadColection(filePath);
                    }
                }
            }
        }
    }
}