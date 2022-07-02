from cs50 import get_string


def main():

    text = get_string("Text: ")
    global numberOL
    numberOL = count_letters(text)
    global numberOW
    numberOW = count_words(text)
    global numberOS
    numberOS = count_sentences(text)
    L = float(average_letters(text))
    S = float(average_sentences(text))

    result = float(round(0.0588 * L - 0.296 * S - 15.8))

    print(f"Number of letters {numberOL}")
    print(f"Number of words {numberOW}")
    print(f"Number of sentences {numberOS}")
    
    if result >= 16:
        print("Grade 16+")
    elif result <= 0:
        print("Before Grade 1")
    else:
        print(f"Grade {int(result)}")


def count_letters(text):

    numberOfLetters = 0

    for i in range(len(text)):
        if text[i].lower() >= "a" and text[i].lower() <= "z":
            numberOfLetters += 1

    return numberOfLetters


def count_words(text):

    numberOfWords = 1

    for i in range(len(text)):
        if text[i] == " ":
            numberOfWords += 1

    return numberOfWords


def count_sentences(text):

    numberOfSentences = 0

    for i in range(len(text)):
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            numberOfSentences += 1

    return numberOfSentences
    

def average_letters(text):

    suma = (float(numberOL) / numberOW) * 100

    return suma


def average_sentences(text):

    suma1 = (float(numberOS) / numberOW) * 100

    return suma1


if __name__ == "__main__":
    main()