using Avalonia.Controls.Shapes;
using FileNotepad.Models;
using ReactiveUI;
using SkiaSharp;
using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Text;

namespace FileNotepad.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        private bool visible_notepad = true, visible_grid = false,visible_open = false, visible_save = false;
        private string text_in_box = string.Empty, text_in_folder = string.Empty;
        private string path=string.Empty, buttonSave_text=string.Empty;
        private int selected_index = 0;

        private ObservableCollection<FilesAndDir> files_colection;

        public MainWindowViewModel()
        {
            files_colection = new ObservableCollection<FilesAndDir>();
            path = Directory.GetCurrentDirectory();
            Open_dir(path);
            buttonSave_text = "Открыть";
        }

        public ObservableCollection<FilesAndDir> Files_colection
        {
            get => files_colection;
            set
            {
                this.RaiseAndSetIfChanged(ref files_colection, value);
            }
        }

        public string DopText1
        {
            get => text_in_folder;
            set
            {
                this.RaiseAndSetIfChanged(ref text_in_folder, value);
                if (text_in_folder != "") ButtonText = "Сохранить";
            }
        }

        public string Text
        {
            get => text_in_box;
            set
            {
                this.RaiseAndSetIfChanged(ref text_in_box, value);
            }
        }

        public int Selected
        {
            get => selected_index;
            set
            {
                this.RaiseAndSetIfChanged(ref selected_index, value);
                if (visible_open == true && visible_save == false)
                {
                    if (files_colection[selected_index] is Files) DopText1 = files_colection[selected_index].Name;
                    else DopText1 = "";
                    ButtonText = "Открыть";
                }
                else if (visible_save == true && visible_open == false)
                {
                    if (files_colection[selected_index] is Files)
                    {
                        ButtonText = "Сохранить";
                        DopText1 = files_colection[selected_index].Name;
                    }
                    else
                    {
                        ButtonText = "Открыть";
                        DopText1 = "";
                    }
                }
            }
        }

        public bool Visible_notepad
        {
            get => visible_notepad;
            set
            {
                this.RaiseAndSetIfChanged(ref visible_notepad, value);
            }
        }

        public bool Visible_grid
        {
            get => visible_grid;
            set
            {
                this.RaiseAndSetIfChanged(ref visible_grid, value);
            }
        }

        public bool Visible_open
        {
            get => visible_open;
            set
            {
                this.RaiseAndSetIfChanged(ref visible_open, value);
            }
        }

        public bool Visible_save
        {
            get => visible_save;
            set
            {
                this.RaiseAndSetIfChanged(ref visible_save, value);
            }
        }

        public string ButtonText
        {
            get => buttonSave_text;
            set
            {
                this.RaiseAndSetIfChanged(ref buttonSave_text, value);
            }
        }

        public void ButtonOpenNotepad()
        {
            DopText1 = string.Empty;
            Visible_notepad = false;
            Visible_grid = true;
            Visible_save = false;
            Visible_open = true;
        }

        public void ButtonSaveNotepad()
        {
            DopText1 = "";
            Selected = 0;
            Visible_notepad = false;
            Visible_grid = true;
            Visible_open = false;
            Visible_save = true;
        }

        public void ButtonCancel()
        {
            text_in_folder = string.Empty;
            Visible_open = false;
            Visible_save = false;
            Visible_grid = false;
            Visible_notepad = true;
        }

        public void ButtonClick()
        {
            if (Visible_open == true) ButtonOpenOpen();
            else if (Visible_save == true) ButtonOpenSave();
        }
        public void ButtonOpenOpen()
        {
            if (files_colection[Selected] is Dir)
            {
                if (files_colection[Selected].Name == "..")
                {
                    var patt = Directory.GetParent(path);
                    if (patt != null)
                    {
                        Open_dir(patt.FullName);
                        path = patt.FullName;
                    }
                    else if (patt == null) Open_dir("");
                }
                else
                {
                    var temp_path = files_colection[selected_index].Path;
                    Open_dir(files_colection[Selected].Path);
                    path = temp_path;
                }
            }
            else
            {
                FileLoad(files_colection[selected_index].Path);
                ButtonCancel();
            }
        }

        public void ButtonOpenSave()
        {
            if (files_colection[Selected] is Dir && DopText1 == "")
            {
                ButtonText = "Открыть";
                if (files_colection[Selected].Name == "..")
                {
                    var patt = Directory.GetParent(path);
                    if (patt != null) Open_dir(patt.FullName);
                    else if (patt == null) Open_dir("");
                    path = patt.FullName;
                }
                else
                {
                    var temp_path = files_colection[selected_index].Path;
                    Open_dir(files_colection[Selected].Path);
                    path = temp_path;
                }
            }
            else if (files_colection[Selected] is Files || DopText1!="")
            {
                if (DopText1 == files_colection[selected_index].Name) FileSave(files_colection[Selected].Path,0);
                else
                {
                    var temp_pat = path;
                    temp_pat += "\\" + DopText1;
                    FileSave(temp_pat,1);
                }
                ButtonCancel();
            }
        }

        public void FileLoad(string ppath)
        {
            string new_text = String.Empty;
            StreamReader sr = new StreamReader(files_colection[selected_index].Path);
            while (sr.EndOfStream != true)
            {
                new_text += sr.ReadLine() + "\n";
            }
            Text = new_text;
        }

        public async void FileSave(string ppath, int flag)
        {
            if (flag == 0)
            {
                using (StreamWriter writer = new StreamWriter(ppath))
                {
                    writer.Write(Text);
                }
            }
            else
            {
                using (FileStream fstream = new FileStream(ppath, FileMode.OpenOrCreate))
                {
                    byte[] buffer = Encoding.Default.GetBytes(Text);
                    await fstream.WriteAsync(buffer, 0, buffer.Length);
                }
            }
        }

        public void Open_dir(string ppath)
        {
            files_colection.Clear();
            if (ppath != "")
            {
                var dirinfo = new DirectoryInfo(ppath);
                files_colection.Add(new Dir(".."));
                foreach (var directory in dirinfo.GetDirectories())
                {
                    files_colection.Add(new Dir(directory));
                }
                foreach (var fileinfo in dirinfo.GetFiles())
                {
                    files_colection.Add(new Files(fileinfo));
                }
            }
            else if (ppath == "")
            {
                foreach(var disk in Directory.GetLogicalDrives())
                {
                    files_colection.Add(new Dir(disk));
                }
            }
            Selected = 0;
        }

        public void DoubleTap()
        {
            if (Visible_open == true) ButtonOpenOpen();
            else if (Visible_save == true) ButtonOpenSave();
        }
    }
}