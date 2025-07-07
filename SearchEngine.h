#pragma once
#include <vcclr.h>
using namespace System;
using namespace System::IO;
using namespace System::Text::RegularExpressions;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

public delegate void OnProgressEvent(int progress);

ref class SearchEngine {
public:
    static array<String^>^ SearchByName(String^ directory, String^ pattern, OnProgressEvent^ onProgress, BackgroundWorker^ worker);
    static array<String^>^ SearchByContent(String^ directory, String^ content, OnProgressEvent^ onProgress, BackgroundWorker^ worker);
    static array<String^>^ SearchByRegex(String^ directory, String^ regexPattern, String^ searchType, OnProgressEvent^ onProgress, BackgroundWorker^ worker);
    static array<String^>^ SearchByMetadata(String^ directory, String^ metadataValue, String^ metadataType, OnProgressEvent^ onProgress, BackgroundWorker^ worker);

    static String^ FormatFileSize(Int64 fileSize) {
        double sizeInKB = fileSize / 1024.0;
        if (sizeInKB < 1000) {
            return String::Format(L"{0:F2} КБ", sizeInKB);
        }
        double sizeInMB = sizeInKB / 1024.0;
        if (sizeInMB < 1000) {
            return String::Format(L"{0:F2} МБ", sizeInMB);
        }
        double sizeInGB = sizeInMB / 1024.0;
        return String::Format(L"{0:F2} ГБ", sizeInGB);
    }

    static ListViewItem^ CreateListViewItemForFile(String^ filePath) {
        FileInfo^ fileInfo = gcnew FileInfo(filePath);
        ListViewItem^ item = gcnew ListViewItem(fileInfo->Name);
        item->SubItems->Add(fileInfo->FullName);
        item->SubItems->Add(FormatFileSize(fileInfo->Length));
        return item;
    }

private:
    static void GetFilesSafely(String^ directory, String^ pattern, List<String^>^ fileList, BackgroundWorker^ worker) {
        if (worker->CancellationPending) return;

        try {
            array<String^>^ files = Directory::GetFiles(directory, pattern);
            fileList->AddRange(files);
        }
        catch (UnauthorizedAccessException^) {
        }
        catch (Exception^ ex) {
            System::Diagnostics::Debug::WriteLine("GetFilesSafely Error in " + directory + ": " + ex->Message);
        }

        try {
            array<String^>^ subDirs = Directory::GetDirectories(directory);
            for each (String ^ subDir in subDirs) {
                if (worker->CancellationPending) return;
                GetFilesSafely(subDir, pattern, fileList, worker);
            }
        }
        catch (UnauthorizedAccessException^) {
        }
        catch (Exception^ ex) {
            System::Diagnostics::Debug::WriteLine("GetFilesSafely SubDir Error in " + directory + ": " + ex->Message);
        }
    }
};