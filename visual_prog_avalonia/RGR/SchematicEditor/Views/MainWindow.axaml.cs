using Avalonia.Controls;
using Avalonia.Controls.Presenters;
using Avalonia.Interactivity;
using SchematicEditor.Models;
using SchematicEditor.ViewModels;
using System.ComponentModel;
using System.IO;
using System.Linq;

namespace SchematicEditor.Views
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainWindowViewModel();
        }

        private async void ClickOpenButton(object sender, RoutedEventArgs eventArgs)
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
                if (path[0] != null && (".xml".Equals(Path.GetExtension(path[0]))) == true)
                {
                    if (File.Exists(path[0]) == true)
                    {
                        SchemaWindow nextWindow = new SchemaWindow(this, path[0]);
                        this.Hide();
                        nextWindow.Show();
                        nextWindow.Closing += CloseMainWindow;
                    }
                    else
                    {
                        var errorWindow = new ErrorWindow("Файл не открылся по выбранному пути");
                        errorWindow.ShowDialog(this);
                    }
                }
            }
        }

        private void ClickDeleteHistory(object sender, RoutedEventArgs eventArgs)
        {
            if (DataContext is MainWindowViewModel mainViewModel)
            {
                if (sender is Button button)
                {
                    if (button.DataContext is ProjectHistory tempProject)
                    {
                        mainViewModel.DeleteProjectInHistory(tempProject);
                    }
                }
            }
        }

        public void ClickCreateButton(object sender, RoutedEventArgs eventArgs)
        {
            var nextWindow = new SchemaWindow(this);
            this.Hide();
            nextWindow.Show();
            nextWindow.Closing += CloseMainWindow;
        }

        public void ClickCloseButton(object sender, RoutedEventArgs eventArgs)
        {
            this.Close();
        }

        private void CloseMainWindow(object? sender, CancelEventArgs e)
        {
            this.Close();
        }

        private void DoubleClickOpen(object sender, RoutedEventArgs e)
        {
            var mwvm = (MainWindowViewModel?)DataContext;
            if (mwvm == null) return;

            var src = e.Source;
            if (src == null) return;

            var name = src.GetType().Name;
            if (name == "ContentPresenter" || name == "TextBlock")
            {
                if (e.Source is ContentPresenter contentPresenter)
                {
                    if (contentPresenter.Content is ProjectHistory element)
                    {
                        if (File.Exists(element.Path) == true)
                        {
                            var nextWindow = new SchemaWindow(this, element.Path);
                            this.Hide();
                            nextWindow.Show();
                            nextWindow.Closing += CloseMainWindow;
                        }
                        else
                        {
                            var errorWindow = new ErrorWindow("Нет файла по выбранному пути.");
                            errorWindow.ShowDialog(this);
                        }
                    }
                }
                else if (e.Source is TextBlock textBlock)
                {
                    if (textBlock.DataContext is ProjectHistory element)
                    {
                        if (File.Exists(element.Path) == true)
                        {
                            var nextWindow = new SchemaWindow(this, element.Path);
                            this.Hide();
                            nextWindow.Show();
                            nextWindow.Closing += CloseMainWindow;
                        }
                        else
                        {
                            var errorWindow = new ErrorWindow("Нет файла по выбранному пути.");
                            errorWindow.ShowDialog(this);
                        }
                    }
                }
            }
        }
    }
}