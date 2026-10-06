package Lab6;

class Time {
    public int hours, minutes, seconds;

    public Time (int hours, int minutes, int seconds) {
        this.hours = hours;
        this.minutes = minutes;
        this.seconds = seconds;
    }
}

public class Ex7 {
    public static Time time_difference (Time a, Time b) {
        int total1 = a.hours * 3600 + a.minutes * 60 + a.seconds;
        int total2 = b.hours * 3600 + b.minutes * 60 + b.seconds;

        int total_result = java.lang.Math.abs(total1 - total2);
        int total_hours = total_result / 3600;
        total_result %= 3600;
        int total_minutes = total_result / 60;
        total_result %= 60;
        int total_seconds = total_result;

        Time result = new Time(total_hours, total_minutes, total_seconds);
        return result;
    }
    public static void main (String[] args) {
        Time t1 = new Time(1, 20, 30);
        Time t2 = new Time(12, 0, 0);

        Time tDelta = time_difference(t1, t2);
        System.out.println("The difference is " + tDelta.hours + " hours, " + tDelta.minutes + " minutes, and " + tDelta.seconds + " seconds");
    }
}
