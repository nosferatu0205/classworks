public class Subject {
	private List<Observer> observers;

	public void Attach(Observer observer){
		this.observers.append(observer);
	}
	public void Detach(Observer observer){
		this.observers.remove(observer);
	}	
	public void Notify(){
		for(Observer observer: observers) 
			observer.update(this);
	}
}

class ClockTimer extends Subject {
	private hour, minute, second;
	public ClockTimer(){
		this.hour = 0;
		this.minute = 0;
		this.second = 0;
	}
	public int GetHour(){
		return this.hour;
	}
	public int GetMinute(){
		return this.minute;
	}
	public int GetSecond(){
		return this.second;
	}

	public void Tick(){
		// State transition happenin
		this.Notify();
	}
}















interface Observer {
	void Update(Subject subject);
}

class DigitalClock implements Observer {
	private Subject subject;

	public DigitalClock(Subject subject){
		this.subject = subject;
		subject.Attach(this);
	}
	public void update(ClockTimer newSubject){ // Is it valid?
		this.subject = newSubject;
		System.out.println(this.subject.GetHour());
		System.out.println(this.subject.GetMinute());
		System.out.println(this.subject.GetSecond());
	}
	public void Draw(){
		System.out.println("Drawing the stuff now.");
		System.out.println(this.subject.GetHour());
		System.out.println(this.subject.GetMinute());
		System.out.println(this.subject.GetSecond());

	}
}

class AnalogClock implements Observer {
	public AnalogClock(ClockTimer clockTimer){
		super(clockTimer);	
	}

	public void someExtraMethods(){}

	@Override
	public void Draw(){
		System.out.println("Drawing analog clock now!");

		System.out.println(this.subject.GetHour());
		System.out.println(this.subject.GetMinute());
		System.out.println(this.subject.GetSecond());
	}
}


class Client {
	public static void main(String[] args){
		Subject timer = new ClockTimer();

		AnalogClock analogClock = new AnalogClock(timer);	
		DigitalClock ditialClock = new DigitalClock(timer);


		AnalogClock analogClock2 = new AnalogClock(timer);	
		AnalogClock analogClock3 = new AnalogClock(timer);	
		AnalogClock analogClock4 = new AnalogClock(timer);	
		AnalogClock analogClock5 = new AnalogClock(timer);	
		AnalogClock analogClock6 = new AnalogClock(timer);	
		AnalogClock analogClock7 = new AnalogClock(timer);	
		AnalogClock analogClock8 = new AnalogClock(timer);	


		analogClock2.draw();
		analogClock3.draw();
		analogClock4.draw();
		analogClock5.draw();
		analogClock6.draw();
		analogClock7.draw();
		analogClock8.draw();
	}
}
