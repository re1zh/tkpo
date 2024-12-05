namespace Phone;

public interface PhoneState
{
    void Call(Phone phone, string number);
    void ReceiveCall(Phone phone);
    void EndCall(Phone phone);
    void AddBalance(Phone phone, double amount);
}

// Состояние "Ожидание"
public class WaitingState : PhoneState
{
    public void Call(Phone phone, string number)
    {
        if (phone.Balance > 0)
        {
            Console.WriteLine($"Набираем номер {number}...");
            phone.SetState(phone.GetCallingState());
        }
        else
        {
            Console.WriteLine("Баланс недостаточен для звонка.");
            phone.SetState(phone.GetBlockedState());
        }
    }

    public void ReceiveCall(Phone phone)
    {
        Console.WriteLine("Входящий звонок...");
        phone.SetState(phone.GetTalkingState());
    }

    public void EndCall(Phone phone)
    {
        Console.WriteLine("Вы не в разговоре.");
    }

    public void AddBalance(Phone phone, double amount)
    {
        phone.Balance += amount;
        Console.WriteLine($"Баланс пополнен на {amount:C}. Текущий баланс: {phone.Balance:C}.");
    }
}

// Состояние "Звонок"
public class CallingState : PhoneState
{
    public void Call(Phone phone, string number)
    {
        Console.WriteLine("Вы уже пытаетесь позвонить.");
    }

    public void ReceiveCall(Phone phone)
    {
        Console.WriteLine("Вы не можете принять звонок во время набора.");
    }

    public void EndCall(Phone phone)
    {
        Console.WriteLine("Звонок завершён.");
        phone.Balance -= 1.0; // Списываем стоимость звонка
        if (phone.Balance <= 0)
        {
            Console.WriteLine("Баланс отрицательный. Телефон заблокирован.");
            phone.SetState(phone.GetBlockedState());
        }
        else
        {
            phone.SetState(phone.GetWaitingState());
        }
    }

    public void AddBalance(Phone phone, double amount)
    {
        phone.Balance += amount;
        Console.WriteLine($"Баланс пополнен на {amount:C}. Текущий баланс: {phone.Balance:C}.");
    }
}

// Состояние "Разговор"
public class TalkingState : PhoneState
{
    public void Call(Phone phone, string number)
    {
        Console.WriteLine("Вы уже в разговоре.");
    }

    public void ReceiveCall(Phone phone)
    {
        Console.WriteLine("Вы не можете принять новый звонок во время разговора.");
    }

    public void EndCall(Phone phone)
    {
        Console.WriteLine("Разговор завершён.");
        phone.Balance -= 10.0;
        if (phone.Balance <= 0)
        {
            Console.WriteLine("Баланс отрицательный. Телефон заблокирован.");
            phone.SetState(phone.GetBlockedState());
        }
        else
        {
            phone.SetState(phone.GetWaitingState());
        }
    }

    public void AddBalance(Phone phone, double amount)
    {
        phone.Balance += amount;
        Console.WriteLine($"Баланс пополнен на {amount:C}. Текущий баланс: {phone.Balance:C}.");
    }
}

// Состояние "Заблокирован"
public class BlockedState : PhoneState
{
    public void Call(Phone phone, string number)
    {
        Console.WriteLine("Телефон заблокирован. Пополните баланс.");
    }

    public void ReceiveCall(Phone phone)
    {
        Console.WriteLine("Телефон заблокирован. Вы не можете принимать звонки.");
    }

    public void EndCall(Phone phone)
    {
        Console.WriteLine("Вы не в разговоре.");
    }

    public void AddBalance(Phone phone, double amount)
    {
        phone.Balance += amount;
        Console.WriteLine($"Баланс пополнен на {amount}. Текущий баланс: {phone.Balance}.");
        if (phone.Balance > 0)
        {
            phone.SetState(phone.GetWaitingState());
        }
    }
}

// Контекст: Телефон
public class Phone
{
    private readonly PhoneState _waitingState;
    private readonly PhoneState _callingState;
    private readonly PhoneState _talkingState;
    private readonly PhoneState _blockedState;

    private PhoneState _currentState;

    public double Balance { get; set; }
    public string Number { get; }
    private int CallProbability { get; }
    
    private readonly Random _random;

    public Phone(string number, double balance, int callProbability)
    {
        Number = number;
        Balance = balance;
        CallProbability = callProbability;
        _random = new Random();

        _waitingState = new WaitingState();
        _callingState = new CallingState();
        _talkingState = new TalkingState();
        _blockedState = new BlockedState();

        _currentState = balance > 0 ? _waitingState : _blockedState;
    }

    public void SetState(PhoneState state) => _currentState = state;
    public PhoneState GetWaitingState() => _waitingState;
    public PhoneState GetCallingState() => _callingState;
    public PhoneState GetTalkingState() => _talkingState;
    public PhoneState GetBlockedState() => _blockedState;

    public void Call(string number) => _currentState.Call(this, number);
    private void ReceiveCall() => _currentState.ReceiveCall(this);
    public void EndCall() => _currentState.EndCall(this);
    public void AddBalance(double amount) => _currentState.AddBalance(this, amount);
    
    public void CheckForIncomingCall()
    {
        if (_currentState == _waitingState && _random.Next(1, 101) <= CallProbability)
        {
            ReceiveCall();
            EndCall();
        }
    }
}

// Тестирование
internal static class Program
{
    private static void Main(string[] args)
    {
        var phone = new Phone("123-456-789", 10.0, 50);
        
        phone.AddBalance(-50.0);
        
        phone.Call("987-654-321");
        phone.EndCall();
        
        phone.AddBalance(100.0);
        
        // Симуляция работы телефона
        Console.WriteLine("Запуск симуляции телефона...");
        for (int i = 0; i < 10; i++) // 10 циклов проверки
        {
            Console.WriteLine($"Проверка {i + 1}:");
            phone.CheckForIncomingCall();
            Thread.Sleep(1000);
        }

        // Звонок вручную
        phone.Call("987-654-321");
        phone.EndCall();
    }
}