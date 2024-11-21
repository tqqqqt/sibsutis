using System.Collections.ObjectModel;

namespace ShemaPaint.Models
{
    public class El_Interface : IElements
    {
        // perem
        private ObservableCollection<Atrib> atribColection;
        private ObservableCollection<Oper> operColection;

        // constr
        public El_Interface() : base()
        {
            atribColection = new ObservableCollection<Atrib>();
            operColection = new ObservableCollection<Oper>();
        }

        // option
        public ObservableCollection<Atrib> AtribColection
        {
            get => atribColection;
            set => SetAndRaise(ref atribColection, value);
        }
        public ObservableCollection<Oper> OperColection
        {
            get => operColection;
            set => SetAndRaise(ref operColection, value);
        }
    }
}
