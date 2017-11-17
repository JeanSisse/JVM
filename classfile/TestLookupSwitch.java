public class TestLookupSwitch{
	public static int chooseFar(int i){
		switch(i){
			case -100:	return -1;
			case 0:		return 0;
			case 100:	return 1;
			default:	return -1;
		}
	}
	public TestLookupSwitch(){
		System.out.println("Ops!");
	}
	public static void main(String args[]){
		System.out.println(TestLookupSwitch.chooseFar(-1));
		System.out.println(TestLookupSwitch.chooseFar(0));
		System.out.println(TestLookupSwitch.chooseFar(100));
		System.out.println(TestLookupSwitch.chooseFar(-100));
		System.out.println(TestLookupSwitch.chooseFar(20));
	}
}
