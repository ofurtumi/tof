public class d3 {
    public static void main(String[] args) {
        System.out.println("int og float: ");

        int a = 50000;
        System.out.println("int 50000*50000 --> " + a * a);

        float b = 1e20f;
        float c = 3.14f;
        System.out.println("float 1e20 + (-1e20 + 3.14) --> " + (b + (-b + c)));

        System.out.println();
        System.out.println("long og double: ");

        long d = (long) Math.pow(2, 63);
        System.out.println("long 2⁶³ * 2⁶³ --> " + d * d);

        double e = 1e20;
        double f = 3.14;
        System.out.println("double 1e20 + (-1e20 + 3.14) --> " + (e + (-e + f)));
    }
}