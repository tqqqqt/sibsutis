using Avalonia.Controls;
using Graphic.ViewModels;

namespace Graphic.Views
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainWindowViewModel(this);
        }
    }
}