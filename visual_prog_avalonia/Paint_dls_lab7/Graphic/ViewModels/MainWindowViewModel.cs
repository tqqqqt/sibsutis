using Avalonia.Controls;
using Graphic.Models;
using Graphic.ViewModels.Pages;
using Graphic.Views;
using ReactiveUI;
using System.Collections.ObjectModel;
using System.Threading.Tasks;

namespace Graphic.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        // peremenie
        private ObservableCollection<IFigure> figures_colection;
        private ViewModelBase[] content_colection;
        private ViewModelBase curent_content;
        private MainWindow mainWindow;
        private ItemsControl items;
        private int listbox_index = -1, combobox_index = 0;
        private LineViewModel line_content;
        private PolyLineViewModel polyline_content;
        private PolygonViewModel polygon_content;
        private RectangleViewModel rectangle_content;
        private EllipseViewModel ellipse_content;
        private PathViewModel path_content;


        // constr
        /*public MainWindowViewModel()
        {
            figures_colection = new ObservableCollection<IFigure>();

            content_colection = new ViewModelBase[]
            {
                new LineViewModel(ref figures_colection),
                new PolyLineViewModel(ref figures_colection),
                new PolygonViewModel(ref figures_colection),
                new RectangleViewModel(ref figures_colection),
                new EllipseViewModel(ref figures_colection),
                new PathViewModel(ref figures_colection)
            };
            curent_content = content_colection[0];
        }*/

        public MainWindowViewModel(MainWindow mw)
        {
            figures_colection = new ObservableCollection<IFigure>();

            mainWindow = mw;
            items = mainWindow.Find<ItemsControl>("canvas");
            //items = mw;

            line_content = new LineViewModel(ref figures_colection);
            polyline_content = new PolyLineViewModel(ref figures_colection);
            polygon_content = new PolygonViewModel(ref figures_colection);
            rectangle_content = new RectangleViewModel(ref figures_colection);
            ellipse_content = new EllipseViewModel(ref figures_colection);
            path_content = new PathViewModel(ref figures_colection);

            content_colection = new ViewModelBase[]
            {
                line_content,
                polyline_content,
                polygon_content,
                rectangle_content,
                ellipse_content,
                path_content
            };
            curent_content = content_colection[0];
        }



        // function
        public async void SaveXML()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            string? result = await saveFileDialog.ShowAsync(mainWindow);
            XmlFunction xml_saver = new XmlFunction();
            xml_saver.XmlSave(result, figures_colection);
        }
        public async Task LoadXML()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            string[]? result = await openFileDialog.ShowAsync(mainWindow);
            XmlFunction xml_loader = new XmlFunction();
            Figures_colection = new ObservableCollection<IFigure>(xml_loader.XmlLoad(result[0]));
            UpdateAllRef();
        }
        public void LoadXML(string path)
        {
            XmlFunction xml_loader = new XmlFunction();
            Figures_colection = new ObservableCollection<IFigure>(xml_loader.XmlLoad(path));
            UpdateAllRef();
        }
        public async Task SaveJSON()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            string? result = await saveFileDialog.ShowAsync(mainWindow);
            JsonFunction json_saver = new JsonFunction();
            json_saver.JsonSave(figures_colection, result);
        }
        public async Task LoadJSON()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            string[]? result = await openFileDialog.ShowAsync(mainWindow);
            JsonFunction json_loader = new JsonFunction();
            Figures_colection = new ObservableCollection<IFigure>(json_loader.JsonLoad(result[0]));
            UpdateAllRef();
        }
        public void LoadJSON(string path)
        {
            JsonFunction json_loader = new JsonFunction();
            Figures_colection = new ObservableCollection<IFigure>(json_loader.JsonLoad(path));
            UpdateAllRef();
        }
        public async Task SavePng()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            string? result = await saveFileDialog.ShowAsync(mainWindow);
            PngFunction png_saver = new PngFunction();
            png_saver.PngSave(result, items);
        }
        public void DeleteBut()
        {
            if (Listbox_index >= 0) figures_colection.RemoveAt(Listbox_index);
        }
        private void UpdateAllRef()
        {
            line_content.UpdateRef(ref figures_colection);
            polyline_content.UpdateRef(ref figures_colection);
            polygon_content.UpdateRef(ref figures_colection);
            rectangle_content.UpdateRef(ref figures_colection);
            ellipse_content.UpdateRef(ref figures_colection);
            path_content.UpdateRef(ref figures_colection);
        }


        // methods for intefrace
        public ObservableCollection<IFigure> Figures_colection
        {
            get => figures_colection;
            set => this.RaiseAndSetIfChanged(ref figures_colection, value);
        }
        public int Listbox_index
        {
            get => listbox_index;
            set
            {
                this.RaiseAndSetIfChanged(ref listbox_index, value);
                if (listbox_index >= 0)
                {
                    if (figures_colection[listbox_index] is Gr_Line)
                    {
                        Combobox_index = 0;
                        line_content.ChangeOption(listbox_index);
                    }
                    else if (figures_colection[listbox_index] is Gr_PolyLine)
                    {
                        Combobox_index = 1;
                        polyline_content.ChangeOption(Listbox_index);
                    }
                    else if (figures_colection[listbox_index] is Gr_Polygon)
                    {
                        Combobox_index = 2;
                        polygon_content.ChangeOption(listbox_index);
                    }
                    else if (figures_colection[listbox_index] is Gr_Rectangle)
                    {
                        Combobox_index = 3;
                        rectangle_content.ChangeOption(listbox_index);
                    }
                    else if (figures_colection[listbox_index] is Gr_Ellipse)
                    {
                        Combobox_index = 4;
                        ellipse_content.ChangeOption(listbox_index);
                    }
                    else if (figures_colection[listbox_index] is Gr_Path)
                    {
                        Combobox_index = 5;
                        path_content.ChangeOption(listbox_index);
                    }
                }
            }
        }
        public int Combobox_index
        {
            get => combobox_index;
            set
            {
                this.RaiseAndSetIfChanged(ref combobox_index, value);
                line_content.Button_cancel();
                polyline_content.Button_cancel();
                polygon_content.Button_cancel();
                rectangle_content.Button_cancel();
                ellipse_content.Button_cancel();
                path_content.Button_cancel();
                Content_colection = content_colection[value];
            }
        }
        public ViewModelBase Content_colection
        {
            get => curent_content;
            set => this.RaiseAndSetIfChanged(ref curent_content, value);
        }
    }
}