using Avalonia.Controls;
using Avalonia.Controls.Presenters;
using Avalonia.Controls.Shapes;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Media;
using Avalonia.VisualTree;
using SchematicEditor.Models;
using SchematicEditor.ViewModels;
using System.Linq;

namespace SchematicEditor.Views
{
    public partial class SchemaWindow : Window
    {
        private Button? curentTouchedTextBlock = null;
        private MainWindow? mainWindow = null;
        private Avalonia.Point pointPressedInCanvas, pointPressedInElement;

        private ISchemaElement? curentElement = null;
        private SchemaLine? curentLine = null;

        public SchemaWindow(MainWindow tempMainWindow)
        {
            InitializeComponent();
            DataContext = new SchemaWindowViewModel();
            mainWindow = tempMainWindow;
            this.KeyUp += SchemaKeyUp;
        }

        public SchemaWindow()
        {
            InitializeComponent();
            DataContext = new SchemaWindowViewModel();
        }

        public SchemaWindow(MainWindow tempMainWindow, string tempPath)
        {
            InitializeComponent();
            DataContext = new SchemaWindowViewModel(tempPath);
            mainWindow = tempMainWindow;
            if (DataContext is SchemaWindowViewModel schemaViewModel)
            {
                if (mainWindow.DataContext is MainWindowViewModel mainViewModel)
                {
                    schemaViewModel.SaveProgramHistory(mainViewModel, tempPath);
                }
            }
            this.KeyUp += SchemaKeyUp;
        }

        public void ClickElementButton(object sender, RoutedEventArgs eventArgs)
        {
            if (curentTouchedTextBlock != sender as Button)
            {
                if (curentTouchedTextBlock != null)
                {
                    curentTouchedTextBlock.Background = SolidColorBrush.Parse("White");
                    var newTextBlock = sender as Button;
                    curentTouchedTextBlock = newTextBlock;
                    curentTouchedTextBlock.Background = SolidColorBrush.Parse("AliceBlue");
                }
                else if (curentTouchedTextBlock == null)
                {
                    var newTextBlock = sender as Button;
                    curentTouchedTextBlock = newTextBlock;
                    curentTouchedTextBlock.Background = SolidColorBrush.Parse("AliceBlue");
                }
            }
            else if (curentTouchedTextBlock == sender as Button)
            {
                curentTouchedTextBlock.Background = SolidColorBrush.Parse("White");
                curentTouchedTextBlock = null;
            }
        }

        protected void ClickOnSchema(object sender, PointerPressedEventArgs pointerPressed)
        {
            pointPressedInCanvas = pointerPressed
                .GetPosition(
                this.GetVisualDescendants()
                .OfType<Canvas>()
                .FirstOrDefault());
            if (DataContext is SchemaWindowViewModel schemaViewModel)
            {
                if (sender is ItemsControl)
                {
                    if (curentTouchedTextBlock != null)
                    {
                        if (curentTouchedTextBlock.Name.Equals("buttonIN") == true)
                        {
                            schemaViewModel.CurentSchemaEdit.ElementColection.Add(new ElementIN
                            {
                                StartPoint = new Avalonia.Point(
                                    pointPressedInCanvas.X, pointPressedInCanvas.Y),
                                IndexElement = schemaViewModel.CurentColectionElement.Count - 1
                            });
                        }
                        else if (curentTouchedTextBlock.Name.Equals("buttonOUT") == true)
                        {
                            schemaViewModel.CurentSchemaEdit.ElementColection.Add(new ElementOUT
                            {
                                StartPoint = new Avalonia.Point(
                                    pointPressedInCanvas.X, pointPressedInCanvas.Y),
                                IndexElement = schemaViewModel.CurentColectionElement.Count - 1
                            });
                        }
                        else if (curentTouchedTextBlock.Name.Equals("buttonAND") == true)
                        {
                            schemaViewModel.CurentSchemaEdit.ElementColection.Add(new ElementAND
                            {
                                StartPoint = new Avalonia.Point(
                                    pointPressedInCanvas.X, pointPressedInCanvas.Y),
                                IndexElement = schemaViewModel.CurentColectionElement.Count - 1
                            });
                        }
                        else if (curentTouchedTextBlock.Name.Equals("buttonOR") == true)
                        {
                            schemaViewModel.CurentSchemaEdit.ElementColection.Add(new ElementOR
                            {
                                StartPoint = new Avalonia.Point(
                                    pointPressedInCanvas.X, pointPressedInCanvas.Y),
                                IndexElement = schemaViewModel.CurentColectionElement.Count - 1
                            });
                        }
                        else if (curentTouchedTextBlock.Name.Equals("buttonNO") == true)
                        {
                            schemaViewModel.CurentSchemaEdit.ElementColection.Add(new ElementNO
                            {
                                StartPoint = new Avalonia.Point(
                                    pointPressedInCanvas.X, pointPressedInCanvas.Y),
                                IndexElement = schemaViewModel.CurentColectionElement.Count - 1
                            });
                        }
                        else if (curentTouchedTextBlock.Name.Equals("buttonXOR") == true)
                        {
                            schemaViewModel.CurentSchemaEdit.ElementColection.Add(new ElementXOR
                            {
                                StartPoint = new Avalonia.Point(
                                    pointPressedInCanvas.X, pointPressedInCanvas.Y),
                                IndexElement = schemaViewModel.CurentColectionElement.Count - 1
                            });
                        }
                        else if (curentTouchedTextBlock.Name.Equals("buttonDE") == true)
                        {
                            schemaViewModel.CurentSchemaEdit.ElementColection.Add(new ElementDE
                            {
                                StartPoint = new Avalonia.Point(
                                    pointPressedInCanvas.X, pointPressedInCanvas.Y),
                                IndexElement = schemaViewModel.CurentColectionElement.Count - 1
                            });
                        }
                    }
                    else
                    {
                        if (pointerPressed.Source is Avalonia.Controls.Shapes.Rectangle rectangle)
                        {
                            curentLine = null;
                            curentElement = rectangle.DataContext as ISchemaElement;
                            // if(rectangle.DataContext is ElementIN elementIN)
                            //{
                            //   elementIN.ChangeInStatus();
                            //}
                            pointPressedInElement = pointerPressed.GetPosition(rectangle);
                            this.PointerMoved += PointerMoveDragShape;
                            this.PointerReleased += PointerReleasDragShape;
                        }
                        else if (pointerPressed.Source is Avalonia.Controls.Shapes.Path path)
                        {
                            curentLine = null;
                            curentElement = path.DataContext as ISchemaElement;
                            pointPressedInElement = pointerPressed.GetPosition(path);
                            this.PointerMoved += PointerMoveDragShape;
                            this.PointerReleased += PointerReleasDragShape;
                        }
                        else if (pointerPressed.Source is Avalonia.Controls.Shapes.Line line)
                        {
                            curentElement = null;
                            curentLine = line.DataContext as SchemaLine;
                        }
                        else if (pointerPressed.Source is Avalonia.Controls.Shapes.Ellipse ellipse)
                        {
                            if (ellipse.DataContext is ISchemaElement element)
                            {
                                int temp = 0;
                                if (ellipse.Name.Contains("IN") == true) temp = 1;
                                else if (ellipse.Name.Contains("OUT") == true) temp = 2;
                                if (temp == 1)
                                {
                                    SchemaLine newLine = new SchemaLine
                                    {
                                        StartPoint = pointPressedInCanvas,
                                        EndPoint = pointPressedInCanvas,
                                        SecondElement = element,
                                        NameSecondElement = ellipse.Name,
                                        TypeSecondElement = 1,
                                        IndexSecondElement = element.IndexElement,
                                    };
                                    schemaViewModel.CurentSchemaEdit.ElementColection.Add(newLine);
                                    this.PointerMoved += PointerMoveDrawLine;
                                    this.PointerReleased += PointerReleasedDrawLine;
                                }
                                else if (temp == 2)
                                {
                                    SchemaLine newLine1 = new SchemaLine
                                    {
                                        StartPoint = pointPressedInCanvas,
                                        EndPoint = pointPressedInCanvas,
                                        FirstElement = element,
                                        NameFirstElement = ellipse.Name,
                                        TypeFirstElement = 2,
                                        IndexFirstElement = element.IndexElement,
                                    };
                                    schemaViewModel.CurentSchemaEdit.ElementColection.Add(newLine1);
                                    this.PointerMoved += PointerMoveDrawLine;
                                    this.PointerReleased += PointerReleasedDrawLine;
                                }
                            }
                        }
                    }
                }
            }
        }

        private void PointerMoveDragShape(object? sender, PointerEventArgs pointerEventArgs)
        {
            if (pointerEventArgs.Source is Avalonia.Controls.Shapes.Rectangle rectangle)
            {
                Avalonia.Point curentPosition = pointerEventArgs
                    .GetPosition(
                    this.GetVisualDescendants()
                    .OfType<Canvas>()
                    .FirstOrDefault());
                if (rectangle.DataContext is ISchemaElement schemaElement)
                {
                    schemaElement.StartPoint = new Avalonia.Point(
                        curentPosition.X - pointPressedInElement.X,
                        curentPosition.Y - pointPressedInElement.Y);
                }
            }
            else if (pointerEventArgs.Source is Avalonia.Controls.Shapes.Path path)
            {
                Avalonia.Point curentPosition = pointerEventArgs
                    .GetPosition(
                    this.GetVisualDescendants()
                    .OfType<Canvas>()
                    .FirstOrDefault());
                if (path.DataContext is ISchemaElement schemaElement)
                {
                    schemaElement.StartPoint = new Avalonia.Point(
                        curentPosition.X - pointPressedInElement.X,
                        curentPosition.Y - pointPressedInElement.Y);
                }
            }
        }

        private void PointerReleasDragShape(object? sender, PointerReleasedEventArgs pREA)
        {
            this.PointerMoved -= PointerMoveDragShape;
            this.PointerReleased -= PointerReleasDragShape;
        }

        private void PointerMoveDrawLine(object? sender, PointerEventArgs pointerEventArgs)
        {
            if (this.DataContext is SchemaWindowViewModel schemaViewModel)
            {
                SchemaLine? lineElement = schemaViewModel.CurentColectionElement[schemaViewModel.CurentColectionElement.Count - 1] as SchemaLine;
                if (lineElement != null)
                {
                    Avalonia.Point curentPosPoint = pointerEventArgs
                        .GetPosition(
                        this.GetVisualDescendants()
                        .OfType<Canvas>()
                        .FirstOrDefault());
                    lineElement.EndPoint = new Avalonia.Point(
                        curentPosPoint.X - 1,
                        curentPosPoint.Y - 1);
                }
            }
        }

        private void PointerReleasedDrawLine(object? sender, PointerReleasedEventArgs pointerReleased)
        {
            this.PointerMoved -= PointerMoveDrawLine;
            this.PointerReleased -= PointerReleasedDrawLine;
            var canvas = this.GetVisualDescendants()
                .OfType<Canvas>()
                .FirstOrDefault(canvas => string.IsNullOrEmpty(canvas.Name) == false && canvas.Name.Equals("editCanvas"));
            var coords = pointerReleased.GetPosition(canvas);
            var element = canvas.InputHitTest(coords);
            SchemaWindowViewModel schemaViewModel = this.DataContext as SchemaWindowViewModel;
            if (element is Ellipse ellipse)
            {
                if (ellipse.DataContext is ISchemaElement schemaElement)
                {
                    SchemaLine line = schemaViewModel.CurentColectionElement[schemaViewModel.CurentColectionElement.Count - 1] as SchemaLine;
                    int tempTypeLine = 0;
                    if (ellipse.Name.Contains("IN") == true) tempTypeLine = 1;
                    else if (ellipse.Name.Contains("OUT") == true) tempTypeLine = 2;
                    if (tempTypeLine == 1)
                    {
                        if (line.SecondElement == null && line.FirstElement != schemaElement && line.TypeFirstElement != tempTypeLine)
                        {
                            line.SecondElement = schemaElement;
                            line.TypeSecondElement = tempTypeLine;
                            line.NameSecondElement = ellipse.Name;
                            line.IndexSecondElement = schemaElement.IndexElement;
                            line.ConectionUpdate();
                            return;
                        }
                    }
                    else if (tempTypeLine == 2)
                    {
                        if (line.FirstElement == null && line.SecondElement != schemaElement && line.TypeSecondElement != tempTypeLine)
                        {
                            line.FirstElement = schemaElement;
                            line.TypeFirstElement = tempTypeLine;
                            line.NameFirstElement = ellipse.Name;
                            line.IndexFirstElement = schemaElement.IndexElement;
                            line.ConectionUpdate();
                            return;
                        }
                    }
                }
            }
            schemaViewModel.CurentColectionElement.RemoveAt(schemaViewModel.CurentColectionElement.Count - 1);
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
                Name = "xml",
                Extensions = new string[] { "xml" }.ToList()
            });
            string? path = await saveFileDialog.ShowAsync(this);
            if (path != null)
            {
                if (DataContext is SchemaWindowViewModel schemaViewModel)
                {
                    schemaViewModel.SaveProjectXML(path);
                    if (mainWindow.DataContext is MainWindowViewModel mainViewModel)
                    {
                        schemaViewModel.SaveProgramHistory(mainViewModel, path);
                    }
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
                Name = "xml",
                Extensions = new string[] { "xml" }.ToList()
            });
            string[]? path = await openFileDialog.ShowAsync(this);
            if (path != null)
            {
                if (path[0] != null)
                {
                    if (DataContext is SchemaWindowViewModel schemaViewModel)
                    {
                        schemaViewModel.LoadProjectXML(path[0]);
                        if (mainWindow.DataContext is MainWindowViewModel mainViewModel)
                        {
                            schemaViewModel.SaveProgramHistory(mainViewModel, path[0]);
                        }
                    }
                }
            }
        }

        public void CreateProject(object sender, RoutedEventArgs eventArgs)
        {
            if (DataContext is SchemaWindowViewModel schemaViewModel)
            {
                schemaViewModel.CreateNewProject();
            }
        }

        public void AddedSchemINProject(object sender, RoutedEventArgs eventArgs)
        {
            if (DataContext is SchemaWindowViewModel schemaViewModel)
            {
                schemaViewModel.CreateNewSchema();
            }
        }

        public void ExitClick(object sender, RoutedEventArgs eventArgs)
        {
            this.Close();
            mainWindow.Close();
        }

        private void DoubleClickEditSchema(object sender, RoutedEventArgs e)
        {
            var swvm = (SchemaWindowViewModel?)DataContext;
            if (swvm == null) return;

            var src = e.Source;
            if (src == null) return;

            var name = src.GetType().Name;
            if (name == "ContentPresenter" || name == "TextBlock")
            {
                if (e.Source is ContentPresenter contentPresenter)
                {
                    if (contentPresenter.Content is Schema element)
                    {
                        swvm.CurentSchemaEdit = element;
                    }
                }
                else if (e.Source is TextBlock textBlock)
                {
                    if (textBlock.DataContext is Schema element)
                    {
                        swvm.CurentSchemaEdit = element;
                    }
                }
            }
        }

        private void DoubleClickElementSchema(object sender, RoutedEventArgs e)
        {
            var swvm = (SchemaWindowViewModel?)DataContext;
            if (swvm == null) return;

            var src = e.Source;
            if (src == null) return;

            var name = src.GetType().Name;
            if (name == "Rectangle")
            {
                if (e.Source is Rectangle rectangle)
                {
                    if (rectangle.DataContext is ElementIN element)
                    {
                        element.ChangeInStatus();
                    }
                }
            }
        }

        private async void DoubleClickChangeNames(object sender, RoutedEventArgs e)
        {
            var schemaViewModel = DataContext as SchemaWindowViewModel;
            if (schemaViewModel == null) return;

            var src = e.Source;
            if (src == null) return;

            var name = src.GetType().Name;
            if (name == "TextBlock")
            {
                if (e.Source is TextBlock textBlock)
                {
                    if (textBlock.DataContext is SchemaWindowViewModel swvm)
                    {
                        var changeNamesWindow = new ChangeNamesWindow(swvm.CurentProject);
                        await changeNamesWindow.ShowDialog(this);
                        swvm.UpdateNames();
                    }
                }
            }
        }

        private void SchemaKeyUp(object? sender, KeyEventArgs e)
        {
            if (DataContext is SchemaWindowViewModel schemaViewModel)
            {
                if (e.Key == Key.Delete)
                {
                    if (curentElement != null)
                    {
                        schemaViewModel.DeleteSchemaElement(curentElement);
                    }
                    else if (curentLine != null)
                    {
                        schemaViewModel.DeleteSchemaLine(curentLine);
                    }
                }
            }
        }

        private void DeleteSchemaButton(object sender, RoutedEventArgs eventArgs)
        {
            if (DataContext is SchemaWindowViewModel schemaViewModel)
            {
                if (sender is Button button)
                {
                    if (button.DataContext is Schema schema)
                    {
                        schemaViewModel.DeleteSchema(schema);
                    }
                }
            }
        }
    }
}
