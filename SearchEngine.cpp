#include "SearchEngine.h"

array<String^>^ SearchEngine::SearchByName(String^ directory, String^ pattern, OnProgressEvent^ onProgress, BackgroundWorker^ worker) {
    try {
        List<String^>^ allFiles = gcnew List<String^>();
        GetFilesSafely(directory, pattern, allFiles, worker);

        int totalFiles = allFiles->Count;
        int processedFiles = 0;

        for each (String ^ file in allFiles) {
            if (worker->CancellationPending) break;
            processedFiles++;
            if (onProgress != nullptr && totalFiles > 0) {
                int progress = 30 + (processedFiles * 70) / totalFiles;
                onProgress(progress);
            }
            worker->ReportProgress(0, allFiles->Count.ToString());
        }
        return allFiles->ToArray();
    }
    catch (Exception^ ex) {
        if (onProgress != nullptr) onProgress(30);
        System::Diagnostics::Debug::WriteLine("SearchByName Error: " + ex->Message);
        return gcnew array<String^>(0);
    }
}

array<String^>^ SearchEngine::SearchByContent(String^ directory, String^ content, OnProgressEvent^ onProgress, BackgroundWorker^ worker) {
    List<String^>^ result = gcnew List<String^>();
    List<String^>^ files = gcnew List<String^>();
    GetFilesSafely(directory, "*.*", files, worker);

    int totalFiles = files->Count;
    int processedFiles = 0;

    for each (String ^ file in files) {
        if (worker->CancellationPending) break;
        try {
            String^ fileContent = File::ReadAllText(file, System::Text::Encoding::GetEncoding(1251));
            if (fileContent->Contains(content)) {
                result->Add(file);
                worker->ReportProgress(0, result->Count.ToString());
            }
        }
        catch (Exception^) {}
        processedFiles++;

        if (onProgress != nullptr && totalFiles > 0) {
            int progress = 30 + (processedFiles * 70) / totalFiles;
            onProgress(progress);
        }
    }
    return result->ToArray();
}

array<String^>^ SearchEngine::SearchByRegex(String^ directory, String^ regexPattern, String^ searchType, OnProgressEvent^ onProgress, BackgroundWorker^ worker) {
    System::Diagnostics::Debug::WriteLine(L"SearchByRegex called with directory: " + directory + L", pattern: " + regexPattern + L", searchType: " + searchType);
    List<String^>^ result = gcnew List<String^>();

    Regex^ regex = nullptr;
    try {
        regex = gcnew Regex(regexPattern);
    }
    catch (ArgumentException^ ex) {
        System::Diagnostics::Debug::WriteLine("Invalid regex pattern: " + ex->Message);
        if (onProgress != nullptr) onProgress(100);
        return gcnew array<String^>(0);
    }

    List<String^>^ files = gcnew List<String^>();
    GetFilesSafely(directory, "*.*", files, worker);

    System::Diagnostics::Debug::WriteLine("Found " + files->Count + " files to process in directory: " + directory);
    if (files->Count == 0) {
        if (onProgress != nullptr) onProgress(100);
        return gcnew array<String^>(0);
    }

    int totalFiles = files->Count;
    int processedFiles = 0;

    for each (String ^ file in files) {
        if (worker->CancellationPending) {
            System::Diagnostics::Debug::WriteLine("SearchByRegex cancelled by user.");
            break;
        }

        try {
            if (searchType == "name") {
                String^ fileName = Path::GetFileName(file);
                System::Diagnostics::Debug::WriteLine("Checking file name: " + fileName);
                if (regex->IsMatch(fileName)) {
                    result->Add(file);
                    System::Diagnostics::Debug::WriteLine("Match found for file: " + file);
                    worker->ReportProgress(0, result->Count.ToString());
                }
            }
            else if (searchType == "content") {
                String^ fileContent = File::ReadAllText(file, System::Text::Encoding::GetEncoding(1251));
                System::Diagnostics::Debug::WriteLine("Checking file content: " + file);
                if (regex->IsMatch(fileContent)) {
                    result->Add(file);
                    System::Diagnostics::Debug::WriteLine("Match found in content for file: " + file);
                    worker->ReportProgress(0, result->Count.ToString());
                }
            }
            else {
                FileInfo^ info = gcnew FileInfo(file);
                String^ metadataValue = nullptr;
                if (searchType == "extension") {
                    metadataValue = info->Extension->ToLower();
                    System::Diagnostics::Debug::WriteLine("Checking extension: " + metadataValue);
                }
                else if (searchType == "size") {
                    metadataValue = info->Length.ToString();
                    System::Diagnostics::Debug::WriteLine("Checking size: " + metadataValue);
                }
                else if (searchType == "date") {
                    metadataValue = info->LastWriteTime.ToString();
                    System::Diagnostics::Debug::WriteLine("Checking date: " + metadataValue);
                }

                if (metadataValue != nullptr && regex->IsMatch(metadataValue)) {
                    result->Add(file);
                    System::Diagnostics::Debug::WriteLine("Match found in metadata for file: " + file);
                    worker->ReportProgress(0, result->Count.ToString());
                }
            }
        }
        catch (Exception^ ex) {
            System::Diagnostics::Debug::WriteLine("SearchByRegex Error at " + file + ": " + ex->Message);
            continue;
        }

        processedFiles++;
        if (onProgress != nullptr && totalFiles > 0) {
            int progress = 30 + (processedFiles * 70) / totalFiles;
            onProgress(progress);
        }
    }

    System::Diagnostics::Debug::WriteLine("SearchByRegex found " + result->Count + " files");
    if (onProgress != nullptr) onProgress(100);
    return result->ToArray();
}

array<String^>^ SearchEngine::SearchByMetadata(String^ directory, String^ metadataValue, String^ metadataType, OnProgressEvent^ onProgress, BackgroundWorker^ worker) {
    System::Diagnostics::Debug::WriteLine("SearchByMetadata called with directory: " + directory + ", value: " + metadataValue + ", type: " + metadataType);
    List<String^>^ result = gcnew List<String^>();
    List<String^>^ files = gcnew List<String^>();
    GetFilesSafely(directory, "*.*", files, worker);

    int totalFiles = files->Count;
    int processedFiles = 0;

    for each (String ^ file in files) {
        if (worker->CancellationPending) break;
        try {
            FileInfo^ info = gcnew FileInfo(file);
            if (metadataType == "extension" && info->Extension->ToLower()->Contains(metadataValue->ToLower())) {
                result->Add(file);
                worker->ReportProgress(0, result->Count.ToString());
            }
            else if (metadataType == "size" && info->Length.ToString()->Contains(metadataValue)) {
                result->Add(file);
                worker->ReportProgress(0, result->Count.ToString());
            }
            else if (metadataType == "date" && info->LastWriteTime.ToString()->Contains(metadataValue)) {
                result->Add(file);
                worker->ReportProgress(0, result->Count.ToString());
            }
        }
        catch (Exception^ ex) {
            System::Diagnostics::Debug::WriteLine("SearchByMetadata Error at " + file + ": " + ex->Message);
            continue;
        }
        processedFiles++;

        if (onProgress != nullptr && totalFiles > 0) {
            int progress = 30 + (processedFiles * 70) / totalFiles;
            onProgress(progress);
        }
    }
    System::Diagnostics::Debug::WriteLine("SearchByMetadata found " + result->Count + " files");
    return result->ToArray();
}