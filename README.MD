# The Odissey Project

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![RISC-V](https://img.shields.io/badge/Architecture-RISC--V-blue)](https://riscv.org/)
[![Status: Alpha](https://img.shields.io/badge/Status-Alpha-orange)](https://github.com/tu-usuario/unbound-pda)

**The Odissey Project** es un proyecto para construir una consola/terminal portátil de código abierto, con un kernel y sistema operativo desarrollados desde cero. El dispositivo combina la filosofía del hardware y software libre, utilizando un procesador RISC-V de 64 bits.

---

## 🎯 Filosofía

The Odissey Project no es solo un dispositivo; es una declaración de principios:

- **Hardware Abierto**: Todos los diseños, esquemáticos y planos de la placa base son públicos y libres (bajo CERN-OHL-S-2.0).
- **Software Libre**: Kernel, sistema operativo, controladores y aplicaciones son de código abierto (MIT/GPL-3.0).
- **Control Total**: Tú decides qué ejecuta tu dispositivo, cómo lo ejecuta y qué datos almacena.
- **Educación y Empoderamiento**: The Odissey Project está diseñado para enseñar, inspirar y dar a cualquiera las herramientas para construir su propio sistema.

---

## 🖥️ Especificaciones de Hardware (Objetivo)

| Componente | Especificación |
| :--- | :--- |
| **CPU** | RISC-V de 64 bits (StarFive JH7110, 4x SiFive U74 @ 1.5GHz) |
| **RAM** | 2GB - 4GB LPDDR4 |
| **Almacenamiento** | eMMC + microSD |
| **Pantalla** | LCD u OLED de 3" o 4" (16:9) |
| **Teclado** | Matriz de botones personalizada (físico, QWERTY) |
| **Señalamiento** | 2 trackpads (puntero + scroll) / 2 botones (clic izquierdo/derecho) |
| **Conectividad** | WiFi 5, Bluetooth 5.0, USB-C (x2), USB-A |
| **Batería** | LiPo 1000mAh (recargable vía USB-C) |
| **Indicadores** | LEDs para carga, encendido, estado de batería |
| **Factor de Forma** | Clamshell (concha), tipo Nintendo 3DS |

---

## 🧠 Software y Sistema Operativo

El corazón del The Odissey Project es su **kernel monolítico** desarrollado desde cero para RISC-V.

### Características Principales (en desarrollo)
- [ ] Arranque bare-metal en QEMU (máquina `virt`)
- [ ] Controlador UART para depuración
- [ ] Gestión de memoria física y virtual
- [ ] Manejo de interrupciones y excepciones
- [ ] Planificador de procesos (round-robin)
- [ ] Llamadas al sistema (syscalls)
- [ ] Espacio de usuario (modo U)
- [ ] Controladores para periféricos (teclado, trackpads, pantalla)
- [ ] Sistema de archivos (FAT32 o ext2)
- [ ] Soporte para ejecutar programas en C/C++
- [ ] Shell interactiva

### Entorno de Desarrollo
- **Compilador**: `riscv64-unknown-elf-gcc`
- **Ensamblador**: `riscv64-unknown-elf-as`
- **Enlazador**: `riscv64-unknown-elf-ld`
- **Emulador**: `qemu-system-riscv64`
- **Depurador**: `gdb-multiarch`

---

## 🗺️ Hoja de Ruta

El desarrollo del The Odissey Project está organizado en fases bien definidas. El estado actual es **Fase 1: Arranque y Kernel Mínimo**.

| Fase | Objetivo | Estado |
| :--- | :--- | :--- |
| **Fase 0** | Configuración del entorno | ✅ Completado |
| **Fase 1** | Arranque y kernel mínimo (Hello World por UART) | ⏳ En progreso |
| **Fase 2** | Gestión de memoria | 🔜 Pendiente |
| **Fase 3** | Manejo de interrupciones y excepciones | 🔜 Pendiente |
| **Fase 4** | Planificador de procesos (scheduler) | 🔜 Pendiente |
| **Fase 5** | Llamadas al sistema (syscalls) | 🔜 Pendiente |
| **Fase 6** | Espacio de usuario y carga de programas | 🔜 Pendiente |
| **Fase 7** | Controladores de periféricos (hardware real) | 🔜 Pendiente |
| **Fase 8** | Aplicaciones y sistema completo | 🔜 Pendiente |
| **Fase 9** | Optimizaciones y extensiones | 🔜 Pendiente |

---

## 🚀 Cómo Empezar

### Prerrequisitos

Asegúrate de tener instaladas las herramientas necesarias:

```bash
# En Ubuntu/Debian
sudo apt update
sudo apt install gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf qemu-system-riscv64 gdb-multiarch
```

### Clonar el Repositorio

```bash
git clone https://github.com/tu-usuario/unbound-pda.git
cd unbound-pda
```
---

## 📂 Estructura del Proyecto

```
unbound-pda/
├── boot/
│   └── boot.s              # Código de arranque en ensamblador
├── kernel/
│   └── kernel.c            # Núcleo del sistema en C
├── drivers/
│   └── uart.c              # Controlador UART
│   └── ...                 # Futuros controladores
├── include/
│   └── uart.h              # Cabeceras públicas
│   └── ...                 # Futuras cabeceras
├── build/                  # Archivos compilados (generado automáticamente)
├── link.ld                 # Script de enlace
├── Makefile                # Sistema de construcción
├── LICENSE                 # Licencia MIT
└── README.md               # Este archivo
```

---

## 📝 Licencia

Este proyecto está licenciado bajo la **Licencia MIT**. Consulta el archivo [LICENSE](LICENSE) para más detalles.

### ¿Qué significa esto para ti?
- ✅ Puedes usar, modificar y distribuir el código libremente.
- ✅ Puedes incluir el código en proyectos comerciales.
- ✅ Solo necesitas dar crédito al autor original.
- ❌ No hay garantía ni responsabilidad por el uso del software.

---

## 🤝 Contribuir

¡Las contribuciones son bienvenidas y muy apreciadas!

### Cómo contribuir

1. **Fork** el repositorio.
2. Crea una rama para tu característica: `git checkout -b feature/nueva-caracteristica`
3. **Commit** tus cambios: `git commit -m 'Añadir nueva característica'`
4. **Push** a la rama: `git push origin feature/nueva-caracteristica`
5. Abre un **Pull Request**.

### Áreas donde necesitamos ayuda

- [ ] Desarrollo del kernel (gestión de memoria, scheduler, syscalls)
- [ ] Controladores de periféricos (teclado, trackpads, pantalla)
- [ ] Diseño de la placa base (esquemáticos, PCB)
- [ ] Diseño de la carcasa (CAD, impresión 3D)
- [ ] Documentación y tutoriales
- [ ] Pruebas en hardware real (cuando esté disponible)

---

## 📚 Recursos y Documentación

- [RISC-V Specification](https://riscv.org/technical/specifications/)
- [OSDev Wiki - RISC-V Bare Bones](https://wiki.osdev.org/RISC-V_Bare_Bones)
- [QEMU Documentation](https://www.qemu.org/docs/master/)
- [StarFive JH7110 Datasheet](https://doc-en.rvspace.org/JH7110/PDF/JH7110_DS.pdf)

---

## 🌟 Agradecimientos

Este proyecto no sería posible sin:
- La comunidad de [OSDev](https://wiki.osdev.org)
- El equipo de [SiFive](https://www.sifive.com/) por su procesador U74
- Los creadores de QEMU, GCC y Binutils
- La comunidad open-source de RISC-V

---

## 📬 Contacto

- **Autor**: [Roybel Carbonell Camejo](https://github.com/luka7634/)
- **GitHub**: [github.com/luka7634/Odissey-Project](https://github.com/luka7634/Odissey-Project)
- **Email**: luka68231@gmail.com

---

**The Odissey Project** — Libera tu hardware. Libera tu software. Libera tu mente.