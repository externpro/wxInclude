/*
  wxInclude
  Kim De Deyn
*/

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

namespace po = boost::program_options;
namespace fs = std::filesystem;

#define WXINCLUDE_INFO	"wxInclude by Kim De Deyn, use --help for more information.\n"

#define WXINCLUDE_HELP	"This tool can be used to convert binary files into a useful C/C++ header.\n" \
  "The primary goal is to provide wxWidgets users an easy way of integrating images in their programs. " \
  "The addition of extra helper macros for wxWidgets can be disabled.\n\n" \
  "It is able to convert multiple files into one header. " \
  "Input can be defined by passing files or the extension masks you want to convert.\n\n" \
  "Example of use:\n\n" \
  "  wxInclude.exe --const --input-file=mydata1.bin\n" \
  "    --input-type=.png --input-type=.bmp\n" \
  "    --output-file=myheader.h mydata2.bin myimage.png\n\n" \
  "Recommended usage (at Space Dynamics Lab):\n" \
  "  wxInclude --const --appendtype --wxnone --respectcase --output-file=foo.hrc foo.png\n"

#define WXINCLUDE_VERSION "Version 1.3, compiled on " __DATE__ " at " __TIME__

#define BUFFER_SIZE 4096

void defineheader_start( std::ostringstream& data, std::string& headername, bool usemacro = true, bool useconst = false )
{
  /* Write info header */
  data << "/*" << std::endl;
  data << "  Automatically generated header by:" << std::endl << std::endl;
  data << "    " << WXINCLUDE_INFO;
  data << "    " << WXINCLUDE_VERSION << std::endl << std::endl;
  data << "  Header: " << headername << std::endl;
  data << "  Macros: " << ( usemacro ? "yes" : "no" ) << std::endl;
  data << "  Const: " << ( useconst ? "yes" : "no" ) << std::endl;
  data << "*/" << std::endl << std::endl;

  /* Prevent multiple defines */
  std::string temp( headername );
  boost::to_upper( temp );
  data << "#ifndef WXINCLUDE_" << temp << "_H" << std::endl;
  data << "#define WXINCLUDE_" << temp << "_H" << std::endl << std::endl;
}

void defineheader_end( std::ostringstream& data, std::string& name )
{
  /* Prevent multiple defines */
  data << "#endif" << std::endl << std::endl;
}

void definemacros( std::ostringstream& data, std::string& includename, bool definestream = true )
{
  /* Include wxWidgets header */
  data << "#include \"" << includename << "\"" << std::endl;

  /* When using default header, include memory stream header!*/
  if ( definestream )
    data << "#include \"wx/mstream.h\"" << std::endl;

  data << std::endl;

  /* Define some useful macros */
  data << "#define wxMEMORY_IMAGE( name ) _wxConvertMemoryToImage( name, sizeof( name ) )" << std::endl;
  data << "#define wxMEMORY_IMAGEEX( name, type ) _wxConvertMemoryToImage( name, sizeof( name ), type )" << std::endl;
  data << "#define wxMEMORY_BITMAP( name ) _wxConvertMemoryToBitmap( name, sizeof( name ) )" << std::endl;
  data << "#define wxMEMORY_BITMAPEX( name, type ) _wxConvertMemoryToBitmap( name, sizeof( name ), type )" << std::endl << std::endl;

  data << "inline wxImage _wxConvertMemoryToImage(const unsigned char* data, int length, wxBitmapType type = wxBITMAP_TYPE_ANY )" << std::endl;
  data << "{" << std::endl;
  data << "    wxMemoryInputStream stream( data, length );" << std::endl;
  data << "    return wxImage( stream, type, -1 );" << std::endl;
  data << "}" << std::endl << std::endl;

  data << "inline wxBitmap _wxConvertMemoryToBitmap(const unsigned char* data, int length, wxBitmapType type = wxBITMAP_TYPE_ANY )" << std::endl;
  data << "{" << std::endl;
  data << "    wxMemoryInputStream stream( data, length );" << std::endl;
  data << "    return wxBitmap( wxImage( stream, type, -1 ), -1 );" << std::endl;
  data << "}" << std::endl << std::endl;
}

static std::vector<std::string> list;

void definefile( std::ostringstream& data, std::ifstream& input, std::string& name, bool useconst = false )
{
  /* Check if already defined */
  std::vector<std::string>::iterator search = std::find( list.begin(), list.end(), name );
  if ( search == list.end() )
  {
    list.push_back( name );
  }
  else
  {
    /* Show warning, object of this name is already processed! */
    std::cout << "Warning: '" << name << "' already defined, processing of new one stopped." << std::endl;
    return;
  }

  /* Define array */
  data << "static" << ( useconst ? " const " : " " ) << "unsigned char " << name << "[] = {";

  int size = static_cast<int>(input.tellg()); // conversion from std::streamoff to int, possible loss of data
  input.seekg( 0, std::ios::beg );

  const unsigned int col_size = 10U;

  for ( int i = 0; i < size; ++i )
  {
    const bool is_last_char = ( i == size - 1 );
    const bool is_first_char_in_row = ( i % col_size ) == 0U;
    const bool is_last_char_in_row = ( i % col_size ) == ( col_size - 1 );

    /* New row? */
    if ( is_first_char_in_row )
    {
      data << std::endl;

      if ( i < size - 1 )
      {
        data << "    "; /* Row's indentation */
      }
    }

    /* Get character and add to array */
    const int c = input.get();

    /*
      Using a static copy of the boost::format string gives a nice performance boost!
      Boost help says using const boost::format fmter(fstring);
      But static is faster and using the object without copy constructor is even faster!
    */
    //static boost::format fmt( "0x%02X" );
    //data << fmt % c;

    /*
      Fast option then... this code is executed allot!
      Still faster then the optimized boost::format use, but not that much!
    */
    static char temp[5];
    snprintf( temp, 5, "0x%02X", c );
    data << temp;

    if ( is_last_char )
    {
      /* Last character */
      data << std::endl;
    }
    else if ( is_last_char_in_row )
    {
      /* Next character is in new row */
      data << ",";
    }
    else
    {
      /* Next character is in same row */
      data << ", ";
    }
  }

  data << "};" << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
  try
  {
    po::options_description desc( "Options" );
    desc.add_options()
      ( "help,h", "Show detailed help." )
      ( "options,p", "Show parameter information." )
      ( "version,v", "Show version information." )
      ( "quiet,q", "Quiet at runtime, not verbose." )
      ( "input-file,i", po::value<std::vector<std::string> >(), "Define file(s) for the conversion input." )
      ( "input-type,I", po::value<std::vector<std::string> >(), "Define file type(s) for automatic conversion of files in the working directory." )
      ( "output-file,o", po::value<std::string>(), "Define file for the conversion output." )
      ( "noheader,h", "Disable adding of header support defines." )
      ( "const,C", "Define array as const." )
      ( "respectcase,r", "Disable converting file types into lower case." )
      ( "wxnone,w", "Disable adding of wxWidgets support macro's." )
      ( "wxheader,W", po::value<std::string>()->default_value( "wx/wx.h" ), "Select the header that includes wxWidgets (precompiled header?)." )
      ( "appendtype,t", "Add the file type at the end of the identifier (myimage_png)." )
    ;

    po::positional_options_description posdesc;
    posdesc.add( "input-file", -1 );

    po::variables_map opt;
    po::store( po::command_line_parser( argc, argv ).options( desc ).positional( posdesc ).run(), opt );
    std::ifstream ifs(fs::path("default.cfg"));
    po::store( po::parse_config_file( ifs, desc ), opt );
    po::notify( opt );

    if ( !opt.count( "quiet" ) )
      std::cout << WXINCLUDE_INFO << std::endl;

    /* Show options when requested */
    if ( opt.count( "options" ) )
    {
      std::cout << desc << std::endl << std::endl;
      exit( 0 );
    }

    /* Show help when requested */
    if ( opt.count( "help" ) )
    {
      std::cout << WXINCLUDE_HELP;
      std::cout << std::endl << desc << std::endl << std::endl;
      exit( 0 );
    }

    /* Show version when requested */
    if ( opt.count( "version" ) )
    {
      std::cout << WXINCLUDE_VERSION << std::endl;
      exit( 0 );
    }

    /* Process */
    if ( opt.count( "input-file" ) || opt.count( "input-type" ) )
    {
      if ( opt.count( "output-file" ) )
      {
        /* Create timer */
        boost::timer::cpu_timer timer;

        /* Create output file */
        std::string headername( opt[ "output-file" ].as<std::string>() );

        fs::path outputpath( headername );
        std::ofstream output( outputpath, std::ios::out | std::ios::trunc | std::ios::binary );

        /* Use buffer */
        char outbuffer[BUFFER_SIZE];
        output.rdbuf()->pubsetbuf( outbuffer, BUFFER_SIZE );

        if ( !output )
          throw std::runtime_error( "Failed to create output file!" );

        if ( !opt.count( "quiet" ) ) /* Show status */
          std::cout << "Build  : file '" << outputpath.filename() << "'..." << std::endl;

        /* Get base name of file */
        headername = outputpath.stem().string();

        /* Data string stream */
        std::ostringstream data;

        /* Write header start when wanted */
        if ( !opt.count( "noheader" ) )
          defineheader_start( data, headername, opt.count( "wxnone" ) ? false : true, opt.count( "const" ) ? true : false );

        /* Get defined or else default wx header */
        std::string includename( opt[ "wxheader" ].as<std::string>() );

        /* Write macros when wanted */
        if ( !opt.count( "wxnone" ) )
          definemacros( data, includename, opt[ "wxheader" ].defaulted() );

        /* Common input buffer */
        char inbuffer[BUFFER_SIZE];

        /* Process input files based on provided list */
        if ( opt.count( "input-file" ) )
        {
          std::vector<std::string> files( opt[ "input-file" ].as<std::vector<std::string> >() );

          for( std::string& file : files )
          {
            fs::path inputpath( file );
            std::string fileext( inputpath.extension().string() );

            std::ifstream input( inputpath, std::ios::in | std::ios::binary | std::ios::ate );
            input.rdbuf()->pubsetbuf( inbuffer, BUFFER_SIZE );

            if ( input.is_open() )
            {
              if ( !opt.count( "quiet" ) ) /* Show status */
                std::cout << "Process: file '" << file << "'..." << std::endl;

              /* Remove extension */
              boost::erase_last( file, fileext );

              if ( !opt.count( "respectcase" ) )
                boost::to_lower( fileext );

              /* Append type */
              if ( opt.count( "appendtype" ) )
              {
                boost::erase_first( fileext, "." );

                /* Static and NO copy constructor for speed */
                static boost::format fmt( "%1%_%2%" );
                file = boost::str( fmt % file % fileext );
              }

              /* Lower case names when wanted */
              if ( !opt.count( "respectcase" ) )
                boost::to_lower( file );

              /* Process file */
              definefile( data, input, file, opt.count( "const" ) ? true : false );
            }
            else
            {
              /* Only show warning, other files need to be processed */
              std::cout << "Warning: input file '" << file << "' failed to open." << std::endl;
            }
          }
        }

        /* Process input files based on provided type */
        if ( opt.count( "input-type" ) )
        {
          const auto types( opt[ "input-type" ].as<std::vector<std::string> >() );

          std::set<fs::path> sorted_img_paths{};

          for ( const auto& dir_entry : fs::directory_iterator{fs::current_path()} )
          {
            for( const std::string& type : types )
            {
              /* Normal file? */
              if ( fs::is_regular_file( dir_entry.path() ) )
              {
                /* Wanted type? */
                const std::string fileext( dir_entry.path().extension().string() );

                bool equals = false;

                if ( opt.count( "respectcase" ) )
                  equals = boost::equals( fileext, type );
                else
                  equals = boost::iequals( fileext, type );

                if ( equals )
                {
                  sorted_img_paths.insert(dir_entry.path());
                }
              }
            }
          }

          for ( const auto& img_path : sorted_img_paths )
          {
            std::ifstream input( img_path, std::ios::in | std::ios::binary | std::ios::ate );
            input.rdbuf()->pubsetbuf( inbuffer, BUFFER_SIZE );

            std::string file( img_path.filename().string() );

            if ( input.is_open() )
            {
              if ( !opt.count( "quiet" ) ) /* Show status */
                std::cout << "Process: file '" << file << "'..." << std::endl;

              std::string fileext( img_path.extension().string() );

              /* Remove extension */
              boost::erase_last( file, fileext );

              /* Append type */
              if ( opt.count( "appendtype" ) )
              {
                boost::erase_first( fileext, "." );

                /* Static and NO copy constructor for speed */
                static boost::format fmt( "%1%_%2%" );
                file = boost::str( fmt % file % fileext );
              }

              /* Lower case names when wanted */
              if ( !opt.count( "respectcase" ) )
                boost::to_lower( file );

              /* Process file */
              definefile( data, input, file, opt.count( "const" ) ? true : false );
            }
            else
            {
              /* Only show warning, other files need to be processed */
              std::cout << "Warning: input file '" << file << "' failed to open." << std::endl;
            }
          }
        }

        /* Write header end when wanted */
        if ( !opt.count( "noheader" ) )
          defineheader_end( data, headername );

        /* Write data to output file */
        output.seekp( 0, std::ios::beg );
        output << data.str();

        if ( !opt.count( "quiet" ) ) /* Show status */
        {
          auto nanoseconds = std::chrono::nanoseconds(timer.elapsed().user + timer.elapsed().system);
          auto seconds = std::chrono::duration_cast<std::chrono::seconds>(nanoseconds);
          std::cout << "Build  : " << seconds.count() << "s needed for conversion of " << list.size() << " files." << std::endl;
        }
      }
      else
      {
        throw std::invalid_argument( "No output defined!" );
      }
    }
    else
    {
      throw std::invalid_argument( "No input defined!" );
    }
  }
  catch( std::exception& e )
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  catch( ... )
  {
    std::cerr << "Error: Exception of unknown type!" << std::endl;
  }

  return 0;
}
