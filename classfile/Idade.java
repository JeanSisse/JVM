
public class Idade {
	
	static int x = 32;
	static double k = 15.4;
	
	public int idade;

	public Idade(){

	}

	public Idade(int idade){
		this.idade = idade;
	}

	public int getIdade(){
		return idade + 1;
	}

	public void setIdade(int idade){
		this.idade = idade;
	}

	public static void main (String[] args){
		System.out.println("Hello World!");

	}
}
