namespace test.sacs
{
    /// <date>Jun 20, 2005</date>
    public class BoundsCheck13 : Test.Framework.TestCase
    {
        private BoundsCheckEntities bce;

        public BoundsCheck13(BoundsCheckEntities bce) :
            base("sacs_boundsCheck_tc13", "sacs_boundsCheck", "DataWriter.write",
                 "Check for correct structs array bounds",
                 "Check that struct arrays smaller than their specified size are not accepted", null)
        {
            this.bce = bce;
        }


        public override Test.Framework.TestResult Run()
        {
            DDS.ReturnCode rc;
            string expResult = "struct array with too small size returns BAD_PARAMETER";
            Test.Framework.TestResult result = new Test.Framework.TestResult(
                expResult,
                string.Empty,
                Test.Framework.TestVerdict.Pass,
                Test.Framework.TestVerdict.Fail);

            if (result.Result != string.Empty)
            {
                return result;
            }

            bce.message2 = new mod.embeddedStructType();
            bce.message2.tstArr = new mod.tst[2];
            for (int i = 0; i < 2; i++) {
                bce.message2.tstArr[i] = new mod.tst(); // Prevent uninitialized array from causing error.
            }
            rc = bce.datawriter2.Write(bce.message2, 0);
            if (rc != DDS.ReturnCode.BadParameter)
            {
                result.Result = "struct array with too small size did NOT return BAD_PARAMETER.";
                return result;
            }
            result.Result = expResult;
            result.Verdict = Test.Framework.TestVerdict.Pass;
            return result;
        }
    }
}
