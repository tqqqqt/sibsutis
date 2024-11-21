using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Shapes;
using Avalonia.Input;
using Avalonia.VisualTree;
using Graphic.Models;
using Graphic.ViewModels;
using System.Linq;

namespace Graphic.Views
{
    public partial class MainWindow : Window
    {
        private Point pointPointerPressed;
        private Point pointerPositionInToShape;
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainWindowViewModel(this);
            AddHandler(DragDrop.DropEvent, Drop);
        }

        private void PointerPressedOn(object sender, PointerPressedEventArgs pointerPressedEventArgs)
        {
            pointPointerPressed = pointerPressedEventArgs
                .GetPosition(
                this.GetVisualDescendants()
                .OfType<Canvas>()
                .FirstOrDefault());
            if (this.DataContext is MainWindowViewModel viewModel)
            {
                if (pointerPressedEventArgs.Source is Shape shape)
                {
                    pointerPositionInToShape = pointerPressedEventArgs.GetPosition(shape);
                    this.PointerMoved += PointerMoveShape;
                    this.PointerReleased += PointerReleseShape;
                }
            }
        }

        private void PointerMoveShape(object? sender, PointerEventArgs pointEventArgs)
        {
            if (pointEventArgs.Source is Shape shape)
            {
                Point currentPointerPosition = pointEventArgs
                    .GetPosition(
                    this.GetVisualDescendants()
                    .OfType<Canvas>()
                    .FirstOrDefault());
                if (shape.DataContext is Gr_Line lin)
                {
                    lin.Pos = new Point(
                        (int)(currentPointerPosition.X - pointerPositionInToShape.X),
                        (int)(currentPointerPosition.Y - pointerPositionInToShape.Y));
                }
                else if (shape.DataContext is Gr_PolyLine pol)
                {
                    pol.Pos = new Point(
                        (int)(currentPointerPosition.X - pointerPositionInToShape.X),
                        (int)(currentPointerPosition.Y - pointerPositionInToShape.Y));
                }
                else if (shape.DataContext is Gr_Polygon polyg)
                {
                    polyg.Pos = new Point(
                        (int)(currentPointerPosition.X - pointerPositionInToShape.X),
                        (int)(currentPointerPosition.Y - pointerPositionInToShape.Y));
                }
                else if (shape.DataContext is Gr_Rectangle rec)
                {
                    rec.Start_point = new Point(
                        (int)(currentPointerPosition.X - pointerPositionInToShape.X),
                        (int)(currentPointerPosition.Y - pointerPositionInToShape.Y));
                }
                else if (shape.DataContext is Gr_Ellipse el)
                {
                    el.StartPoint = new Point(
                        (int)(currentPointerPosition.X - pointerPositionInToShape.X),
                        (int)(currentPointerPosition.Y - pointerPositionInToShape.Y));
                }
                else if (shape.DataContext is Gr_Path pa)
                {
                    pa.Pos = new Point(
                        (int)(currentPointerPosition.X - pointerPositionInToShape.X),
                        (int)(currentPointerPosition.Y - pointerPositionInToShape.Y));
                }
            }
        }

        private void PointerReleseShape(object? sender, PointerReleasedEventArgs pointEventArgs)
        {
            this.PointerMoved -= PointerMoveShape;
            this.PointerReleased -= PointerReleseShape;
        }

        private void Drop(object? sender, DragEventArgs dragEventArgs)
        {
            if (dragEventArgs.Data.Contains(DataFormats.FileNames) == true)
            {
                string? fileName = dragEventArgs.Data.GetFileNames()?.FirstOrDefault();
                if (fileName != null)
                {
                    if (this.DataContext is MainWindowViewModel dataContext)
                    {
                        if (".json".Equals(System.IO.Path.GetExtension(fileName)) == true)
                        {
                            dataContext.LoadJSON(fileName);
                        }
                        else if (".xml".Equals(System.IO.Path.GetExtension(fileName)) == true)
                        {
                            dataContext.LoadXML(fileName);
                        }
                    }
                }
            }
        }
    }
}