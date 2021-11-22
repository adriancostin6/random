import sys, getopt, os
from PyPDF2 import PdfFileReader, PdfFileWriter

def print_help():
    print("""\
Split PDF file into multiple output files according to user input.
Usage: python split-pdf.py <input> [options]
Input:
    - /path/to/input/pdf that you want to split
Options:
    -h | --help: view this menu
    -p | --page: splits only on specified pages
    -r | --range: splits pages in specified range
    -t | --tie: tie all output files in one PDF
    -d | --decrypt: decrypts PDF if it is password protected
    -e | --encrypt: encrypts PDF output
Example:
    Splitting:
        python split-pdf.py ~/example.pdf -p 2,3,4
        python split-pdf.py ~/example.pdf -r 2,4
        python split-pdf.py ~/example.pdf -t -r 2,4 
    Decryption:
        python split-pdf.py ~/example.pdf -t -d -r 2,4
    Encryption:
        python split-pdf.py ~/example.pdf -e -r 2,4""")
    sys.exit(2)

def parse_args():
    if not os.path.exists(sys.argv[1]):
        print("Invalid input file, try again.")
        print("For help run: python split-pdf.py -h")
        sys.exit(2)

    try:
        opts, args = getopt.getopt(sys.argv[2:], "p:r:td:e:",
                                   ["page=", "range=",
                                    "tie", "decrypt=", "encrypt="])
    except getopt.GetoptError as err:
        print(err)
        print("Check help by running: python split-pdf.py")
        sys.exit(2)

    parsed_args = {
        "pdfpath": sys.argv[1],
        "pdfname": os.path.basename(sys.argv[1]),
        "pages": "",
        "range": "",
        "tie": False,
        "decrypt": "",
        "encrypt": ""
    }

    for o, a in opts:
        if o in ("-p", "--page"):
            parsed_args["pages"] = a
        elif o in ("-r", "--range"):
            parsed_args["range"] = a
        elif o in ("-t", "--tie"):
                parsed_args["tie"] = True
        elif o in ("-d", "--decrypt"):
                parsed_args["decrypt"] = a
        elif o in ("-e", "--encrypt"):
            parsed_args["encrypt"] = a
        else:
            assert False, "unknown options"
    return parsed_args

def ReadPDF(args):
    input_pdf = PdfFileReader(args["pdfpath"])

    if (input_pdf.isEncrypted):
        if (not input_pdf.decrypt(args["decrypt"])):
            print("Decryption failed, wrong password. Try again")

    return input_pdf


def SplitPDF(pdf, args):
    # No pages or range specified, split page by page
    if (not args["pages"]):
        if(not args["range"]):
            for i in range(pdf.numPages):
                output = PdfFileWriter()
                output.addPage(pdf.getPage(i))
                with open("page-{no}-{name}"
                          .format(no=i, name=args["pdfname"]), "wb") as OutputStream:
                    output.write(OutputStream)

def main():
    if len(sys.argv) == 1:
        print_help()

    args = parse_args()

    print(args)


    pdf = ReadPDF(args)

    SplitPDF(pdf, args)

if __name__ == "__main__":
    main()

