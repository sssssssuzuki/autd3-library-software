using AUTD3SharpTest.Test;

namespace AUTD3SharpTest
{
    internal class Program
    {
        private static void Main()
        {
            SimpleExample.Test();
            BesselExample.Test();
            HoloGainExample.Test();
            LateralExmaple.Test();

            // Following test needs 2 AUTDs
            //GroupedGainTest.Test();
        }
    }
}