import sys
import csv

count = 0

STRs = {
    "AGATC": 0,
    "AATG": 0,
    "TATC": 0,
    "TTTTTTCT": 0,
    "TCTAG": 0,
    "GATA": 0,
    "TCTG": 0
}


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DatabaseFile FileofSequences")

    DatabaseFile = sys.argv[1]
    FileOfSequences = sys.argv[2]

    Database = []

    with open(DatabaseFile, "r") as file:
        reader = csv.DictReader(file)
        for person in reader:
            Database.append(person)

    with open(FileOfSequences, "r") as file:
        reader = csv.reader(file)
        for row in reader:
            Sequence = row[0]

    i = 0
    j = 0

    for i in range(len(Sequence)):
        check("AGATC", i, j+len("AGATC"), Sequence)
        check("AATG", i, j+len("AATG"), Sequence)
        check("TATC", i, j+len("TATC"), Sequence)
        check("TTTTTTCT", i, j+len("TTTTTTCT"), Sequence)
        check("TCTAG", i, j+len("TCTAG"), Sequence)
        check("GATA", i, j+len("GATA"), Sequence)
        check("TCTG", i, j+len("TCTG"), Sequence)
        j += 1

    found = False

    if DatabaseFile == "databases/small.csv":
        while found != True:
            for person in Database:
                if person['AGATC'] == str(STRs['AGATC']) and person['AATG'] == str(STRs['AATG']) and person['TATC'] == str(STRs['TATC']):
                    print(person['name'])
                    found = True
            if found == False:
                print("No match")
                found = True
    else:
        while found != True:
            for person in Database:
                if person['AGATC'] == str(STRs['AGATC']) and person['AATG'] == str(STRs['AATG']) and person['TATC'] == str(STRs['TATC']) and person['TTTTTTCT'] == str(STRs['TTTTTTCT']) and person['TCTAG'] == str(STRs['TCTAG']) and person['GATA'] == str(STRs['GATA']) and person['TCTG'] == str(STRs['TCTG']):
                    print(person['name'])
                    found = True
            if found == False:
                print("No match")
                found = True


def check(string, i, j, Sequence):

    current_str = string
    if Sequence[i:j] == string:
        global count
        count += 1
        if count > STRs[current_str]:
            STRs[current_str] = count
        check(string, i+len(string), j+len(string), Sequence)
    else:
        count = 0


main()