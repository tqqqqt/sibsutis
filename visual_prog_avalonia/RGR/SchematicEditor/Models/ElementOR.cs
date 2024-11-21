namespace SchematicEditor.Models
{
    public class ElementOR : ISchemaElement
    {
        private int inSignal1, inSignal2;

        public ElementOR()
        {
            inSignal1 = 0;
            inSignal2 = 0;
            OutSignal = 0;
        }

        public int InSignal1
        {
            get => inSignal1;
            set
            {
                SetAndRaise(ref inSignal1, value);
                CalculateOutSignal();
            }
        }

        public int InSignal2
        {
            get => inSignal2;
            set
            {
                SetAndRaise(ref inSignal2, value);
                CalculateOutSignal();
            }
        }

        private void CalculateOutSignal()
        {
            OutSignal = InSignal1 | InSignal2;
        }
    }
}
