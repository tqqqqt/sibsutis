using ReactiveUI;
using Student.Models;
using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Reactive;
using System.Xml.Serialization;

namespace Student.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        private StudenItem St;
        private ObservableCollection<StudenItem> StudentItem;
        
        public int SelectedIndex;
        public string New_text = "";
        public int s1, s2, s3, s4, s5;
        public double sr_1, sr_2, sr_3, sr_4, sr_5, sr_sr;

        public MainWindowViewModel()
        {
            ShowItem = ReactiveCommand.Create<StudenItem>(item => St = item);
            StudentItem = new ObservableCollection<StudenItem>();

            StudentItem.Add(new StudenItem
            {
                St_FIO = "Паша Пупкин",
                St_Pr1 = 2,
                St_Pr2 = 1,
                St_Pr3 = 2,
                St_Pr4 = 2,
                St_Pr5 = 2,
                St_Sr = (double)(2 + 1 + 2 + 2 + 2) / 5
            });
            StudentItem.Add(new StudenItem
            {
                St_FIO = "Толя Васькин",
                St_Pr1 = 1,
                St_Pr2 = 2,
                St_Pr3 = 1,
                St_Pr4 = 2,
                St_Pr5 = 0,
                St_Sr = (double)(1 + 2 + 1 + 2 + 1) / 5
            });

            AddedItem = ReactiveCommand.Create(() =>
            {
                StudentItem.Add(new StudenItem
                {
                    St_FIO = New_text,
                    St_Pr1 = s1 - 1,
                    St_Pr2 = s2 - 1,
                    St_Pr3 = s3 - 1,
                    St_Pr4 = s4 - 1,
                    St_Pr5 = s5 - 1,
                    St_Sr = (double)((s1 - 1) + (s2 - 1) + (s3 - 1) + (s4 - 1) + (s5 - 1)) / 5
                });
                CheckSR(StudentItem);
                SR1 = Math.Round(sr_1,2); SR2 = Math.Round(sr_2,2); SR3 = Math.Round(sr_3,2); SR4 = Math.Round(sr_4,2); SR5 = Math.Round(sr_5,2); SRR = Math.Round(sr_sr,2);
            });

            RemoveItem = ReactiveCommand.Create(() =>
            {
                StudentItem.RemoveAt(SelectedIndex);
                CheckSR(StudentItem);
                SR1 = sr_1; SR2 = sr_2; SR3 = sr_3; SR4 = sr_4; SR5 = sr_5; SRR = sr_sr;
            });

            SaveItem = ReactiveCommand.Create(() =>
            {
                XmlSerializer xs = new XmlSerializer(typeof(ObservableCollection<StudenItem>));
                using (StreamWriter wr = new StreamWriter(@"..\..\stud.xml"))
                {
                    xs.Serialize(wr, StudentItem);
                }
            });

            LoadItem = ReactiveCommand.Create(() =>
            {
                StudentItem.Clear();
                XmlSerializer xs = new XmlSerializer(typeof(ObservableCollection<StudenItem>));
                using (StreamReader rd = new StreamReader(@"..\..\stud.xml"))
                {
                    StudentItem = xs.Deserialize(rd) as ObservableCollection<StudenItem>;
                }
                StudentItems = StudentItem;
                CheckSR(StudentItem);
                SR1 = sr_1; SR2 = sr_2; SR3 = sr_3; SR4 = sr_4; SR5 = sr_5; SRR = sr_sr;
            });

            CheckSR(StudentItem);
        }
        public double SR1 { get => sr_1; set { sr_1 = -0.001; this.RaiseAndSetIfChanged(ref sr_1, value); } }
        public double SR2 { get => sr_2; set { sr_2 -= 0.001; this.RaiseAndSetIfChanged(ref sr_2, value); } }
        public double SR3 { get => sr_3; set { sr_3 -= 0.001; this.RaiseAndSetIfChanged(ref sr_3, value); } }
        public double SR4 { get => sr_4; set { sr_4 -= 0.001; this.RaiseAndSetIfChanged(ref sr_4, value); } }
        public double SR5 { get => sr_5; set { sr_5 -= 0.001; this.RaiseAndSetIfChanged(ref sr_5, value); } }
        public double SRR { get => sr_sr; set { sr_sr -= 0.001; this.RaiseAndSetIfChanged(ref sr_sr, value); } }
        public int PR1
        {
            get => s1;
            set => this.RaiseAndSetIfChanged(ref s1, value);
        }
        public int PR2
        {
            get => s2;
            set => this.RaiseAndSetIfChanged(ref s2, value);
        }
        public int PR3
        {
            get => s3;
            set => this.RaiseAndSetIfChanged(ref s3, value);
        }
        public int PR4
        {
            get => s4;
            set => this.RaiseAndSetIfChanged(ref s4, value);
        }
        public int PR5
        {
            get => s5;
            set => this.RaiseAndSetIfChanged(ref s5, value);
        }

        public int SelecetInd
        {
            get => SelectedIndex;
            set => this.RaiseAndSetIfChanged(ref SelectedIndex, value);
        }

        public string New_TEXT
        {
            get => New_text;
            set => this.RaiseAndSetIfChanged(ref New_text, value);
        }
        public StudenItem ST
        {
            get => St;
            set => this.RaiseAndSetIfChanged(ref St, value);
        }

        public ObservableCollection<StudenItem> StudentItems
        {
            get => StudentItem;
            set
            {
                StudentItem = null;
                this.RaiseAndSetIfChanged(ref StudentItem, value);
            }
        }

        public void CheckSR(ObservableCollection<StudenItem> stud)
        {
            var stt = StudentItem;
            sr_1 = 0; sr_2 = 0; sr_3 = 0; sr_4 = 0; sr_5 = 0; sr_sr = 0;
            for (int i = 0; i < stud.Count(); i += 1)
            {
                sr_1 += stt[i].St_Pr1;
                sr_2 += stt[i].St_Pr2;
                sr_3 += stt[i].St_Pr3;
                sr_4 += stt[i].St_Pr4;
                sr_5 += stt[i].St_Pr5;
                sr_sr += stt[i].St_Sr;
            }
            sr_1 /= stud.Count();
            Math.Round(sr_1);
            sr_2 /= stud.Count();
            Math.Round(sr_2, 2);
            sr_3 /= stud.Count();
            Math.Round(sr_3, 2);
            sr_4 /= stud.Count();
            Math.Round(sr_4, 2);
            sr_5 /= stud.Count();
            Math.Round(sr_5, 2);
            sr_sr /= stud.Count();
            Math.Round(sr_sr, 2);
        }


        private ReactiveCommand<StudenItem, Unit> ShowItem { get; }
        public ReactiveCommand<Unit, Unit> RemoveItem { get; }
        public ReactiveCommand<Unit, Unit> AddedItem { get; }
        public ReactiveCommand<Unit, Unit> SaveItem { get; }
        public ReactiveCommand<Unit, Unit> LoadItem { get; }
    }
}
