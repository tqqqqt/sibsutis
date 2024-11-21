namespace SchematicEditor.Models
{
    public class ElementNO : ISchemaElement
    {
        private int inSignal;

        public ElementNO()
        {
            InSignal = 0;
            //OutSignal = 0;
        }

        public int InSignal
        {
            get => inSignal;
            set
            {
                SetAndRaise(ref inSignal, value);
                CalculateOutSignal();
            }
        }

        private void CalculateOutSignal()
        {
            OutSignal = (InSignal == 0) ? 1 : 0;
        }
    }
}
