#include <SFML/Audio.hpp>
#include <complex>
#include <valarray>

// Функция для выполнения быстрого преобразования Фурье
void fft(std::valarray<std::complex<double>>& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    // разделяй и властвуй
    std::valarray<std::complex<double>> even = x[std::slice(0, N/2, 2)];
    std::valarray<std::complex<double>>  odd = x[std::slice(1, N/2, 2)];

    // рекурсивный вызов
    fft(even);
    fft(odd);

    // сбор результата
    for (size_t k = 0; k < N/2; ++k)
    {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

int main()
{
    // Загрузка аудиофайла
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("music/overwall killer.wav"))
        return -1;

    // Получение отсчетов аудиосигнала
    const sf::Int16* samples = buffer.getSamples();
    std::size_t count = buffer.getSampleCount();

    // Преобразование отсчетов в комплексные числа
    std::valarray<std::complex<double>> data(count);
    for (std::size_t i = 0; i < count; ++i)
        data[i] = samples[i];

    // Выполнение преобразования Фурье
    fft(data);

    // Вывод результатов
    for (std::size_t i = 0; i < count; ++i)
        std::cout << i << ": " << std::abs(data[i]) << std::endl;

    return 0;
}