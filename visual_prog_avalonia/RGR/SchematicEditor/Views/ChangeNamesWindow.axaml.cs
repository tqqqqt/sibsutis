using Avalonia.Controls;
using Avalonia.Interactivity;
using SchematicEditor.Models;
using SchematicEditor.ViewModels;

namespace SchematicEditor.Views
{
    public partial class ChangeNamesWindow : Window
    {
        public ChangeNamesWindow()
        {
            InitializeComponent();
        }

        public ChangeNamesWindow(Project sendProject)
        {
            InitializeComponent();
            DataContext = new ChangeNamesWindowViewModel(sendProject);
        }

        private void ButtonSaveClick(object sender, RoutedEventArgs e)
        {
            if (sender is Button button)
            {
                if (button.Name == "exit")
                {
                    this.Close();
                }
            }
        }
    }
}
