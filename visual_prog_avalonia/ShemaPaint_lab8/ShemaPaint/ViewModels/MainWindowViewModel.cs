using Avalonia.Controls;
using ReactiveUI;
using ShemaPaint.Models;
using ShemaPaint.Views;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;

namespace ShemaPaint.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        // perem
        private bool eventClass = false, eventInterface = false, eventMove = false,
            eventLine = false, eventChangeOption = false, eventChangeForm = false,
            eventDelete = false;
        private bool lineNasled = false, lineRealiz = false, lineZavis = false,
            lineAgreg = false, lineCompos = false, lineAsoc = false;
        private ObservableCollection<IFigures> elementColection;
        private ObservableCollection<ISaverLoaderFactory> saverLoaderFactoryColection;
        private MainWindow? mainWindow;
        private ItemsControl? itemsControl;


        // constr
        public MainWindowViewModel(MainWindow mw)
        {
            elementColection = new ObservableCollection<IFigures>();
            saverLoaderFactoryColection = new ObservableCollection<ISaverLoaderFactory>
            {
                new XMLSaverLoaderFactory(),
                new JSONSaverLoaderFactory(),
                new YAMLSaverLoaderFactory(),
            };
            mainWindow = mw;
            itemsControl = mainWindow.Find<ItemsControl>("canvas");
        }
        public MainWindowViewModel()
        {
            elementColection = new ObservableCollection<IFigures>();
            saverLoaderFactoryColection = new ObservableCollection<ISaverLoaderFactory>
            {
                new XMLSaverLoaderFactory(),
                new JSONSaverLoaderFactory(),
            };
        }


        // option
        // struct
        public ObservableCollection<IFigures> ElementColection
        {
            get => elementColection;
            set => this.RaiseAndSetIfChanged(ref elementColection, value);
        }
        private ObservableCollection<ISaverLoaderFactory> SaverLoaderFactoryColection
        {
            get => saverLoaderFactoryColection;
        }
        // main events
        public bool EventLine
        {
            get => eventLine;
            set => this.RaiseAndSetIfChanged(ref eventLine, value);
        }
        public bool EventClass
        {
            get => eventClass;
            set => this.RaiseAndSetIfChanged(ref eventClass, value);
        }
        public bool EventInterface
        {
            get => eventInterface;
            set => this.RaiseAndSetIfChanged(ref eventInterface, value);
        }
        public bool EventMove
        {
            get => eventMove;
            set => this.RaiseAndSetIfChanged(ref eventMove, value);
        }
        public bool EventChangeOption
        {
            get => eventChangeOption;
            set => this.RaiseAndSetIfChanged(ref eventChangeOption, value);
        }
        public bool EventChangeForm
        {
            get => eventChangeForm;
            set => this.RaiseAndSetIfChanged(ref eventChangeForm, value);
        }
        public bool EventDelete
        {
            get => eventDelete;
            set => this.RaiseAndSetIfChanged(ref eventDelete, value);
        }
        // lines event
        public bool LineNasled
        {
            get => lineNasled;
            set => this.RaiseAndSetIfChanged(ref lineNasled, value);
        }
        public bool LineRealiz
        {
            get => lineRealiz;
            set => this.RaiseAndSetIfChanged(ref lineRealiz, value);
        }
        public bool LineZavis
        {
            get => lineZavis;
            set => this.RaiseAndSetIfChanged(ref lineZavis, value);
        }
        public bool LineAgreg
        {
            get => lineAgreg;
            set => this.RaiseAndSetIfChanged(ref lineAgreg, value);
        }
        public bool LineCompos
        {
            get => lineCompos;
            set => this.RaiseAndSetIfChanged(ref lineCompos, value);
        }
        public bool LineAsoc
        {
            get => lineAsoc;
            set => this.RaiseAndSetIfChanged(ref lineAsoc, value);
        }


        // function
        public void SaveColection(string path)
        {
            if (".png".Equals(Path.GetExtension(path)) == true)
            {
                var pngColectionSaver = new PNGSaver();
                pngColectionSaver.Save(itemsControl, path);
            }
            else
            {
                var colectionSave = SaverLoaderFactoryColection
                    .FirstOrDefault(factory => factory.IsMatch(path) == true)?
                    .CreateSaver();
                if (colectionSave != null)
                {
                    colectionSave.Save(ElementColection, path);
                }
            }
        }

        public void LoadColection(string path)
        {
            var colectionLoad = SaverLoaderFactoryColection
                .FirstOrDefault(factory => factory.IsMatch(path) == true)?
                .CreateLoader();
            ElementColection = new ObservableCollection<IFigures>(colectionLoad.Load(path));
            ILines tempLines = new LineAgreg();
            foreach (var line in ElementColection)
            {
                if (line is ILines lines) lines.PathUpdate();
            }
            tempLines.ConnectUpdate(ElementColection);
        }
    }
}