using Avalonia.Controls;
using SchematicEditor.ViewModels;

namespace SchematicEditor.Views
{
    public partial class ErrorWindow : Window
    {
        public ErrorWindow()
        {
            InitializeComponent();
        }

        public ErrorWindow(string sendError)
        {
            InitializeComponent();
            DataContext = new ErrorWindowViewModel(sendError);
        }
    }
}
