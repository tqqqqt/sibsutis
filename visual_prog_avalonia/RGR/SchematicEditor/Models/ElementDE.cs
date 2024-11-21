namespace SchematicEditor.Models
{
    public class ElementDE : ISchemaElement
    {
        private int inSignal1, inSignal2;

        public ElementDE()
        {
            inSignal1 = 0;
            inSignal2 = 0;
            OutSignal = 0;
            OutSignal2 = 0;
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
            int temp1 = (InSignal2 == 0) ? 1 : 0, temp2 = InSignal2;
            OutSignal = temp1 & InSignal1;
            OutSignal2 = temp2 & InSignal1;
        }
    }
}
