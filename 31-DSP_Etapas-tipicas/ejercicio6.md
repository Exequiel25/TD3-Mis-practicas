Para resolver estos problemas, sigamos los siguientes pasos:

### 1. Nivel de cuantización $ q $ del ADC

El nivel de cuantización $ q $ se puede calcular usando la fórmula:

$$ q = \frac{V\_{\text{rango}}}{2^n} $$

donde:

- $ V\_{\text{rango}} $ es el rango total de voltaje del ADC.
- $ n $ es el número de bits del ADC.

En este caso, el rango total de voltaje es $ \pm 5 $ V, lo que significa que $ V\_{\text{rango}} = 10 $ V, y el número de bits $ n = 12 $.

Entonces,

$$ q = \frac{10 \, \text{V}}{2^{12}} = \frac{10 \, \text{V}}{4096} \approx 0.00244 \, \text{V} $$

### 2. Nivel de SNR del ADC

El nivel de SNR (Signal-to-Noise Ratio) para un ADC ideal se puede calcular usando la fórmula:

$$ \text{SNR}\_{\text{ADC}} = 6.02n + 1.76 \, \text{dB} $$

donde $ n $ es el número de bits del ADC.

Para un ADC de 12 bits:

$$ \text{SNR}\_{\text{ADC}} = 6.02 \times 12 + 1.76 = 72.24 + 1.76 = 74 \, \text{dB} $$

Sin embargo, si se aplica una señal compleja de 4 V pico a pico, debemos considerar el rango de la señal en relación con el rango del ADC. La señal de 4 V pico a pico tiene una amplitud de 2 V (de -2 V a +2 V), que es menor que el rango total del ADC de 10 V.

El SNR se puede ajustar considerando la relación entre la amplitud de la señal y el rango del ADC. La relación de amplitud es:

$$ \text{Relación de amplitud} = \frac{4 \, \text{V}}{10 \, \text{V}} = 0.4 $$

El SNR ajustado se puede calcular como:

$$ \text{SNR}_{\text{ajustado}} = \text{SNR}_{\text{ADC}} + 20 \log\_{10}(\text{Relación de amplitud}) $$

$$ \text{SNR}_{\text{ajustado}} = 74 \, \text{dB} + 20 \log_{10}(0.4) $$

$$ \text{SNR}_{\text{ajustado}} = 74 \, \text{dB} + 20 \log_{10}(0.4) \approx 74 \, \text{dB} + 20 \times (-0.398) $$

$$ \text{SNR}\_{\text{ajustado}} \approx 74 \, \text{dB} - 7.96 \, \text{dB} $$

$$ \text{SNR}\_{\text{ajustado}} \approx 66.04 \, \text{dB} $$

Por lo tanto, el nivel de SNR esperado para una señal compleja de 4 V pico a pico es aproximadamente 66.04 dB.
