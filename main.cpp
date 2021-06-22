#include <memory>
#include <cstdlib>
#include <restbed>
#include "Freight_Path.h"

using namespace std;
using namespace restbed;

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        const auto request = session->get_request( );

        string output = "handling...";

        int mission_id = std::stoi(request->get_query_parameter("mission_id"));
        output += "mission_id = " + to_string(mission_id);

        Freight_Path path(mission_id);

        output += path.find_route();

//        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, output, { { "Content-Length", to_string(output.length()) } } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/freight" );
    resource->set_method_handler( "GET", post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
