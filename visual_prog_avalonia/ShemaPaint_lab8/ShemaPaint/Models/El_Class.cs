using System.Collections.ObjectModel;

namespace ShemaPaint.Models
{
    public class El_Class : IElements
    {
        // perem
        private ObservableCollection<Atrib> atrib_colection;
        private ObservableCollection<Oper> oper_colection;

        // constr
        public El_Class() : base()
        {
            atrib_colection = new ObservableCollection<Atrib>();
            oper_colection = new ObservableCollection<Oper>();
        }

        // option
        public ObservableCollection<Atrib> Atrib_colection
        {
            get => atrib_colection;
            set => SetAndRaise(ref atrib_colection, value);
        }
        public ObservableCollection<Oper> Oper_colection
        {
            get => oper_colection;
            set => SetAndRaise(ref oper_colection, value);
        }
    }
}
