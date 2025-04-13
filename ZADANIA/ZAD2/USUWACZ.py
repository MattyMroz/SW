import os
import re
import sys

# --- Konfiguracja ---
# Rozszerzenia plików do przetworzenia
TARGET_EXTENSIONS = ('.c', '.cpp', '.h', '.hpp')
# Katalog startowy (katalog, w którym znajduje się skrypt)
START_DIRECTORY = os.path.dirname(os.path.abspath(__file__))
# --------------------


def remove_c_comments(code):
    """
    Usuwa komentarze C (// i /* */) z podanego stringa kodu oraz znaki białe.

    Uwaga: Może niepoprawnie obsługiwać komentarze wewnątrz literałów stringowych/znakowych.
    """
    # Krok 1: Usuń komentarze wieloliniowe /* ... */
    # re.DOTALL sprawia, że '.' dopasowuje również znaki nowej linii
    # .*? to dopasowanie niezachłanne (non-greedy), aby obsłużyć np. /* com1 */ code /* com2 */
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)

    # Krok 2: Usuń komentarze jednoliniowe // ...
    # re.MULTILINE sprawia, że '$' dopasowuje koniec każdej linii, a nie tylko koniec stringa
    code = re.sub(r'//.*?$', '', code, flags=re.MULTILINE)

    # Krok 3: Usuń znaki białe (spacje, tabulatory, nowe linie)
    code = re.sub(r'\s+', '', code)

    return code


def process_directory(directory):
    """
    Przetwarza rekursywnie pliki w podanym katalogu.
    """
    print(f"Przeszukiwanie katalogu: {directory}")
    processed_files = 0
    modified_files = 0

    for root, dirs, files in os.walk(directory):
        # Pomijaj ukryte foldery (np. .git, .vscode) - opcjonalne
        dirs[:] = [d for d in dirs if not d.startswith('.')]

        for filename in files:
            if filename.endswith(TARGET_EXTENSIONS):
                filepath = os.path.join(root, filename)
                print(f"  -> Przetwarzanie pliku: {filepath}")
                processed_files += 1
                try:
                    # Odczytaj plik (spróbuj z UTF-8, ignoruj błędy)
                    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f_in:
                        original_content = f_in.read()

                    # Usuń komentarze i znaki białe
                    modified_content = remove_c_comments(original_content)

                    # Zapisz plik tylko jeśli zawartość się zmieniła
                    if modified_content != original_content:
                        # Zapisz zmiany (nadpisz plik)
                        with open(filepath, 'w', encoding='utf-8') as f_out:
                            f_out.write(modified_content)
                        print(
                            f"      [*] Komentarze i znaki białe usunięte, plik zapisany.")
                        modified_files += 1
                    else:
                        print(
                            f"      [ ] Brak zmian do wprowadzenia w pliku.")

                except Exception as e:
                    print(
                        f"      [!] BŁĄD podczas przetwarzania pliku {filepath}: {e}", file=sys.stderr)

    return processed_files, modified_files


if __name__ == "__main__":
    print("--------------------------------------------------")
    print("Skrypt do usuwania komentarzy C/C++ i znaków białych")
    print(f"Katalog startowy: {START_DIRECTORY}")
    print(f"Przetwarzane rozszerzenia: {', '.join(TARGET_EXTENSIONS)}")
    print("--------------------------------------------------")
    print("\n!!! OSTRZEŻENIE !!!")
    print("Ten skrypt nadpisuje oryginalne pliki.")
    print("Upewnij się, że masz kopię zapasową lub używasz systemu kontroli wersji (np. Git).")
    print("Skrypt może niepoprawnie usunąć kod, jeśli sekwencje // lub /* */")
    print("znajdują się wewnątrz literałów stringowych lub znakowych.")
    print("Usunięcie znaków białych może wpłynąć na czytelność i działanie kodu.")
    print("--------------------------------------------------\n")

    # Potwierdzenie od użytkownika
    # Możesz usunąć tę część, jeśli chcesz, aby skrypt działał od razu,
    # ale jest to zalecane ze względów bezpieczeństwa.
    confirm = input("Czy chcesz kontynuować? (wpisz 'tak'): ")
    if confirm.lower() != 'tak':
        print("Anulowano.")
        sys.exit(0)

    print("\nRozpoczynanie przetwarzania...")
    total_processed, total_modified = process_directory(START_DIRECTORY)
    print("\n--------------------------------------------------")
    print("Zakończono przetwarzanie.")
    print(f"Przetworzono plików: {total_processed}")
    print(f"Zmodyfikowano plików: {total_modified}")
    print("--------------------------------------------------")
